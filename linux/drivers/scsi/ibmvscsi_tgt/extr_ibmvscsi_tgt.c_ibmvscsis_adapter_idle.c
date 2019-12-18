#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timer_pops; } ;
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct scsi_info {int flags; int state; int resume_state; scalar_t__ phyp_acr_state; int phyp_acr_flags; int /*<<< orphan*/  new_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  credit; int /*<<< orphan*/  debit; TYPE_2__ rsp_q_timer; TYPE_1__ tport; int /*<<< orphan*/  unconfig; } ;

/* Variables and functions */
 int CFG_SLEEPING ; 
 int CONNECTED ; 
 int DISCONNECT_SCHEDULED ; 
#define  ERR_DISCONNECT 132 
#define  ERR_DISCONNECTED 131 
#define  ERR_DISCONNECT_RECONNECT 130 
 int PREP_FOR_SUSPEND_PENDING ; 
 int PRESERVE_FLAG_FIELDS ; 
 int RESPONSE_Q_DOWN ; 
 int SCHEDULE_DISCONNECT ; 
 int TRANS_EVENT ; 
#define  UNCONFIGURING 129 
 int WAIT_CONNECTION ; 
 int WAIT_ENABLED ; 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  ibmvscsis_free_cmd_qs (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_free_command_q (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_poll_cmd_q (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 long ibmvscsis_ready_for_suspend (struct scsi_info*,int) ; 
 int /*<<< orphan*/  ibmvscsis_reset_queue (struct scsi_info*) ; 
 int /*<<< orphan*/  isync () ; 

__attribute__((used)) static void ibmvscsis_adapter_idle(struct scsi_info *vscsi)
{
	int free_qs = false;
	long rc = 0;

	dev_dbg(&vscsi->dev, "adapter_idle: flags 0x%x, state 0x%hx\n",
		vscsi->flags, vscsi->state);

	/* Only need to free qs if we're disconnecting from client */
	if (vscsi->state != WAIT_CONNECTION || vscsi->flags & TRANS_EVENT)
		free_qs = true;

	switch (vscsi->state) {
	case UNCONFIGURING:
		ibmvscsis_free_command_q(vscsi);
		dma_rmb();
		isync();
		if (vscsi->flags & CFG_SLEEPING) {
			vscsi->flags &= ~CFG_SLEEPING;
			complete(&vscsi->unconfig);
		}
		break;
	case ERR_DISCONNECT_RECONNECT:
		ibmvscsis_reset_queue(vscsi);
		dev_dbg(&vscsi->dev, "adapter_idle, disc_rec: flags 0x%x\n",
			vscsi->flags);
		break;

	case ERR_DISCONNECT:
		ibmvscsis_free_command_q(vscsi);
		vscsi->flags &= ~(SCHEDULE_DISCONNECT | DISCONNECT_SCHEDULED);
		vscsi->flags |= RESPONSE_Q_DOWN;
		if (vscsi->tport.enabled)
			vscsi->state = ERR_DISCONNECTED;
		else
			vscsi->state = WAIT_ENABLED;
		dev_dbg(&vscsi->dev, "adapter_idle, disc: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		break;

	case WAIT_IDLE:
		vscsi->rsp_q_timer.timer_pops = 0;
		vscsi->debit = 0;
		vscsi->credit = 0;
		if (vscsi->flags & PREP_FOR_SUSPEND_PENDING) {
			vscsi->state = vscsi->resume_state;
			vscsi->resume_state = 0;
			rc = ibmvscsis_ready_for_suspend(vscsi, true);
			vscsi->flags &= ~DISCONNECT_SCHEDULED;
			if (rc)
				break;
		} else if (vscsi->flags & TRANS_EVENT) {
			vscsi->state = WAIT_CONNECTION;
			vscsi->flags &= PRESERVE_FLAG_FIELDS;
		} else {
			vscsi->state = CONNECTED;
			vscsi->flags &= ~DISCONNECT_SCHEDULED;
		}

		dev_dbg(&vscsi->dev, "adapter_idle, wait: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		ibmvscsis_poll_cmd_q(vscsi);
		break;

	case ERR_DISCONNECTED:
		vscsi->flags &= ~DISCONNECT_SCHEDULED;
		dev_dbg(&vscsi->dev, "adapter_idle, disconnected: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		break;

	default:
		dev_err(&vscsi->dev, "adapter_idle: in invalid state %d\n",
			vscsi->state);
		break;
	}

	if (free_qs)
		ibmvscsis_free_cmd_qs(vscsi);

	/*
	 * There is a timing window where we could lose a disconnect request.
	 * The known path to this window occurs during the DISCONNECT_RECONNECT
	 * case above: reset_queue calls free_command_q, which will release the
	 * interrupt lock.  During that time, a new post_disconnect call can be
	 * made with a "more severe" state (DISCONNECT or UNCONFIGURING).
	 * Because the DISCONNECT_SCHEDULED flag is already set, post_disconnect
	 * will only set the new_state.  Now free_command_q reacquires the intr
	 * lock and clears the DISCONNECT_SCHEDULED flag (using PRESERVE_FLAG_
	 * FIELDS), and the disconnect is lost.  This is particularly bad when
	 * the new disconnect was for UNCONFIGURING, since the unconfigure hangs
	 * forever.
	 * Fix is that free command queue sets acr state and acr flags if there
	 * is a change under the lock
	 * note free command queue writes to this state it clears it
	 * before releasing the lock, different drivers call the free command
	 * queue different times so dont initialize above
	 */
	if (vscsi->phyp_acr_state != 0)	{
		/*
		 * set any bits in flags that may have been cleared by
		 * a call to free command queue in switch statement
		 * or reset queue
		 */
		vscsi->flags |= vscsi->phyp_acr_flags;
		ibmvscsis_post_disconnect(vscsi, vscsi->phyp_acr_state, 0);
		vscsi->phyp_acr_state = 0;
		vscsi->phyp_acr_flags = 0;

		dev_dbg(&vscsi->dev, "adapter_idle: flags 0x%x, state 0x%hx, acr_flags 0x%x, acr_state 0x%hx\n",
			vscsi->flags, vscsi->state, vscsi->phyp_acr_flags,
			vscsi->phyp_acr_state);
	}

	dev_dbg(&vscsi->dev, "Leaving adapter_idle: flags 0x%x, state 0x%hx, new_state 0x%x\n",
		vscsi->flags, vscsi->state, vscsi->new_state);
}