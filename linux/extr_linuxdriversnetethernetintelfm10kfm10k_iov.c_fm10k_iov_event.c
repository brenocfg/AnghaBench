#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* connect ) (struct fm10k_hw*,TYPE_4__*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct fm10k_vf_info {TYPE_4__ mbx; } ;
struct fm10k_iov_data {int num_vfs; struct fm10k_vf_info* vf_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_resources ) (struct fm10k_hw*,struct fm10k_vf_info*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ iov; } ;
struct fm10k_intfc {struct fm10k_iov_data* iov_data; struct fm10k_hw hw; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_EICR ; 
 int FM10K_EICR_VFLR ; 
 int /*<<< orphan*/  FM10K_PFVFLRE (int) ; 
 int /*<<< orphan*/  READ_ONCE (struct fm10k_iov_data*) ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,TYPE_4__*) ; 

s32 fm10k_iov_event(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_iov_data *iov_data;
	s64 vflre;
	int i;

	/* if there is no iov_data then there is no mailbox to process */
	if (!READ_ONCE(interface->iov_data))
		return 0;

	rcu_read_lock();

	iov_data = interface->iov_data;

	/* check again now that we are in the RCU block */
	if (!iov_data)
		goto read_unlock;

	if (!(fm10k_read_reg(hw, FM10K_EICR) & FM10K_EICR_VFLR))
		goto read_unlock;

	/* read VFLRE to determine if any VFs have been reset */
	vflre = fm10k_read_reg(hw, FM10K_PFVFLRE(1));
	vflre <<= 32;
	vflre |= fm10k_read_reg(hw, FM10K_PFVFLRE(0));

	i = iov_data->num_vfs;

	for (vflre <<= 64 - i; vflre && i--; vflre += vflre) {
		struct fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		if (vflre >= 0)
			continue;

		hw->iov.ops.reset_resources(hw, vf_info);
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	}

read_unlock:
	rcu_read_unlock();

	return 0;
}