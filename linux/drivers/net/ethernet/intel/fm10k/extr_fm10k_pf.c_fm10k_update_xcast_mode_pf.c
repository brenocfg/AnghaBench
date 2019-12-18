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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,int*) ;} ;
struct fm10k_mbx_info {TYPE_1__ ops; } ;
struct fm10k_hw {struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_PF_ATTR_ID_XCAST_MODE ; 
 int /*<<< orphan*/  FM10K_PF_MSG_ID_XCAST_MODES ; 
 scalar_t__ FM10K_XCAST_MODE_NONE ; 
 int /*<<< orphan*/  fm10k_glort_valid_pf (struct fm10k_hw*,int) ; 
 int /*<<< orphan*/  fm10k_tlv_attr_put_u32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int*) ; 

__attribute__((used)) static s32 fm10k_update_xcast_mode_pf(struct fm10k_hw *hw, u16 glort, u8 mode)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[3], xcast_mode;

	if (mode > FM10K_XCAST_MODE_NONE)
		return FM10K_ERR_PARAM;

	/* if glort is not valid return error */
	if (!fm10k_glort_valid_pf(hw, glort))
		return FM10K_ERR_PARAM;

	/* write xcast mode as a single u32 value,
	 * lower 16 bits: glort
	 * upper 16 bits: mode
	 */
	xcast_mode = ((u32)mode << 16) | glort;

	/* generate message requesting to change xcast mode */
	fm10k_tlv_msg_init(msg, FM10K_PF_MSG_ID_XCAST_MODES);
	fm10k_tlv_attr_put_u32(msg, FM10K_PF_ATTR_ID_XCAST_MODE, xcast_mode);

	/* load onto outgoing mailbox */
	return mbx->ops.enqueue_tx(hw, mbx, msg);
}