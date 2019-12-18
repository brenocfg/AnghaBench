#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* process ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;int /*<<< orphan*/  (* connect ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;} ;
struct fm10k_mbx_info {TYPE_4__ ops; int /*<<< orphan*/  timeout; } ;
struct fm10k_vf_info {scalar_t__ vf_flags; int /*<<< orphan*/  glort; struct fm10k_mbx_info mbx; } ;
struct fm10k_iov_data {int next_vf_mbx; int num_vfs; struct fm10k_vf_info* vf_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* tx_ready ) (TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* process ) (struct fm10k_hw*,TYPE_5__*) ;} ;
struct TYPE_11__ {scalar_t__ state; TYPE_3__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* reset_resources ) (struct fm10k_hw*,struct fm10k_vf_info*) ;int /*<<< orphan*/  (* reset_lport ) (struct fm10k_hw*,struct fm10k_vf_info*) ;} ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_5__ mbx; TYPE_2__ iov; } ;
struct fm10k_intfc {int /*<<< orphan*/  hw_sm_mbx_full; struct fm10k_iov_data* iov_data; struct fm10k_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ FM10K_STATE_OPEN ; 
 int /*<<< orphan*/  FM10K_VFMBX_MSG_MTU ; 
 int /*<<< orphan*/  READ_ONCE (struct fm10k_iov_data*) ; 
 int /*<<< orphan*/  fm10k_clear_macvlan_queue (struct fm10k_intfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_glort_valid_pf (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_service_event_schedule (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  stub3 (struct fm10k_hw*,struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  stub4 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 

s32 fm10k_iov_mbx(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_iov_data *iov_data;
	int i;

	/* if there is no iov_data then there is no mailbox to process */
	if (!READ_ONCE(interface->iov_data))
		return 0;

	rcu_read_lock();

	iov_data = interface->iov_data;

	/* check again now that we are in the RCU block */
	if (!iov_data)
		goto read_unlock;

	/* lock the mailbox for transmit and receive */
	fm10k_mbx_lock(interface);

	/* Most VF messages sent to the PF cause the PF to respond by
	 * requesting from the SM mailbox. This means that too many VF
	 * messages processed at once could cause a mailbox timeout on the PF.
	 * To prevent this, store a pointer to the next VF mbx to process. Use
	 * that as the start of the loop so that we don't starve whichever VF
	 * got ignored on the previous run.
	 */
process_mbx:
	for (i = iov_data->next_vf_mbx ? : iov_data->num_vfs; i--;) {
		struct fm10k_vf_info *vf_info = &iov_data->vf_info[i];
		struct fm10k_mbx_info *mbx = &vf_info->mbx;
		u16 glort = vf_info->glort;

		/* process the SM mailbox first to drain outgoing messages */
		hw->mbx.ops.process(hw, &hw->mbx);

		/* verify port mapping is valid, if not reset port */
		if (vf_info->vf_flags && !fm10k_glort_valid_pf(hw, glort)) {
			hw->iov.ops.reset_lport(hw, vf_info);
			fm10k_clear_macvlan_queue(interface, glort, false);
		}

		/* reset VFs that have mailbox timed out */
		if (!mbx->timeout) {
			hw->iov.ops.reset_resources(hw, vf_info);
			mbx->ops.connect(hw, mbx);
		}

		/* guarantee we have free space in the SM mailbox */
		if (hw->mbx.state == FM10K_STATE_OPEN &&
		    !hw->mbx.ops.tx_ready(&hw->mbx, FM10K_VFMBX_MSG_MTU)) {
			/* keep track of how many times this occurs */
			interface->hw_sm_mbx_full++;

			/* make sure we try again momentarily */
			fm10k_service_event_schedule(interface);

			break;
		}

		/* cleanup mailbox and process received messages */
		mbx->ops.process(hw, mbx);
	}

	/* if we stopped processing mailboxes early, update next_vf_mbx.
	 * Otherwise, reset next_vf_mbx, and restart loop so that we process
	 * the remaining mailboxes we skipped at the start.
	 */
	if (i >= 0) {
		iov_data->next_vf_mbx = i + 1;
	} else if (iov_data->next_vf_mbx) {
		iov_data->next_vf_mbx = 0;
		goto process_mbx;
	}

	/* free the lock */
	fm10k_mbx_unlock(interface);

read_unlock:
	rcu_read_unlock();

	return 0;
}