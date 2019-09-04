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

/* Variables and functions */
 int /*<<< orphan*/  FM10K_VF_MSG_ID_MSIX ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm10k_update_int_moderator_vf(struct fm10k_hw *hw)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[1];

	/* generate MSI-X request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MSIX);

	/* load onto outgoing mailbox */
	mbx->ops.enqueue_tx(hw, mbx, msg);
}