#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS0_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS1_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS2_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS3_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS4_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_RX_COS5_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_RX_COS0_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_RX_COS1_PRIORITY_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_RX_COS2_PRIORITY_MASK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_pfc_nig_rx_priority_mask(struct bnx2x *bp,
					   u8 cos_entry,
					   u32 priority_mask, u8 port)
{
	u32 nig_reg_rx_priority_mask_add = 0;

	switch (cos_entry) {
	case 0:
	     nig_reg_rx_priority_mask_add = (port) ?
		 NIG_REG_P1_RX_COS0_PRIORITY_MASK :
		 NIG_REG_P0_RX_COS0_PRIORITY_MASK;
	     break;
	case 1:
	    nig_reg_rx_priority_mask_add = (port) ?
		NIG_REG_P1_RX_COS1_PRIORITY_MASK :
		NIG_REG_P0_RX_COS1_PRIORITY_MASK;
	    break;
	case 2:
	    nig_reg_rx_priority_mask_add = (port) ?
		NIG_REG_P1_RX_COS2_PRIORITY_MASK :
		NIG_REG_P0_RX_COS2_PRIORITY_MASK;
	    break;
	case 3:
	    if (port)
		return -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS3_PRIORITY_MASK;
	    break;
	case 4:
	    if (port)
		return -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS4_PRIORITY_MASK;
	    break;
	case 5:
	    if (port)
		return -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS5_PRIORITY_MASK;
	    break;
	}

	REG_WR(bp, nig_reg_rx_priority_mask_add, priority_mask);

	return 0;
}