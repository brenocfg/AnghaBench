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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ;} ;
struct fm10k_mbx_info {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  dglort_map; } ;
struct fm10k_hw {TYPE_1__ mac; struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  FM10K_LPORT_STATE_MSG_DISABLE ; 
 int /*<<< orphan*/  FM10K_VF_MSG_ID_LPORT_STATE ; 
 int /*<<< orphan*/  fm10k_tlv_attr_put_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 fm10k_update_lport_state_vf(struct fm10k_hw *hw, u16 glort,
				       u16 count, bool enable)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[2];

	/* reset glort mask 0 as we have to wait to be enabled */
	hw->mac.dglort_map = FM10K_DGLORTMAP_NONE;

	/* generate port state request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
	if (!enable)
		fm10k_tlv_attr_put_bool(msg, FM10K_LPORT_STATE_MSG_DISABLE);

	/* load onto outgoing mailbox */
	return mbx->ops.enqueue_tx(hw, mbx, msg);
}