#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ;} ;
struct fm10k_mbx_info {TYPE_1__ ops; } ;
struct fm10k_hw {struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_PF_MSG_ID_LPORT_MAP ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 fm10k_request_lport_map_pf(struct fm10k_hw *hw)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[1];

	/* issue request asking for LPORT map */
	fm10k_tlv_msg_init(msg, FM10K_PF_MSG_ID_LPORT_MAP);

	/* load onto outgoing mailbox */
	return mbx->ops.enqueue_tx(hw, mbx, msg);
}