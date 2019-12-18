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
typedef  int u32 ;
struct bfa_ioc {int dummy; } ;

/* Variables and functions */
 int BFA_REG_ADDRMSK (struct bfa_ioc*) ; 
 int BFA_STATUS_EINVAL ; 
 int BFA_STATUS_OK ; 

__attribute__((used)) static int
bna_reg_offset_check(struct bfa_ioc *ioc, u32 offset, u32 len)
{
	u8 area;

	/* check [16:15] */
	area = (offset >> 15) & 0x7;
	if (area == 0) {
		/* PCIe core register */
		if (offset + (len << 2) > 0x8000)	/* 8k dwords or 32KB */
			return BFA_STATUS_EINVAL;
	} else if (area == 0x1) {
		/* CB 32 KB memory page */
		if (offset + (len << 2) > 0x10000)	/* 8k dwords or 32KB */
			return BFA_STATUS_EINVAL;
	} else {
		/* CB register space 64KB */
		if (offset + (len << 2) > BFA_REG_ADDRMSK(ioc))
			return BFA_STATUS_EINVAL;
	}
	return BFA_STATUS_OK;
}