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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_vf_info {scalar_t__ glort; scalar_t__ vf_flags; TYPE_2__ mbx; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ FM10K_VF_FLAG_ENABLED (struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  FM10K_VF_MSG_ID_LPORT_STATE ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_update_lport_state_pf (struct fm10k_hw*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm10k_iov_reset_lport_pf(struct fm10k_hw *hw,
				     struct fm10k_vf_info *vf_info)
{
	u32 msg[1];

	/* need to disable the port if it is already enabled */
	if (FM10K_VF_FLAG_ENABLED(vf_info)) {
		/* notify switch that this port has been disabled */
		fm10k_update_lport_state_pf(hw, vf_info->glort, 1, false);

		/* generate port state response to notify VF it is not ready */
		fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
		vf_info->mbx.ops.enqueue_tx(hw, &vf_info->mbx, msg);
	}

	/* clear flags and glort if it exists */
	vf_info->vf_flags = 0;
	vf_info->glort = 0;
}