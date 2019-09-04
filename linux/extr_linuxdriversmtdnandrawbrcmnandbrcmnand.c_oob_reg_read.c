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
typedef  scalar_t__ u16 ;
struct brcmnand_controller {int max_oob; scalar_t__* reg_offsets; } ;

/* Variables and functions */
 size_t BRCMNAND_OOB_READ_10_BASE ; 
 size_t BRCMNAND_OOB_READ_BASE ; 
 int nand_readreg (struct brcmnand_controller*,scalar_t__) ; 

__attribute__((used)) static inline u8 oob_reg_read(struct brcmnand_controller *ctrl, u32 offs)
{
	u16 offset0, offset10, reg_offs;

	offset0 = ctrl->reg_offsets[BRCMNAND_OOB_READ_BASE];
	offset10 = ctrl->reg_offsets[BRCMNAND_OOB_READ_10_BASE];

	if (offs >= ctrl->max_oob)
		return 0x77;

	if (offs >= 16 && offset10)
		reg_offs = offset10 + ((offs - 0x10) & ~0x03);
	else
		reg_offs = offset0 + (offs & ~0x03);

	return nand_readreg(ctrl, reg_offs) >> (24 - ((offs & 0x03) << 3));
}