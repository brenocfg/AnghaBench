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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct brcmnand_controller {int reg_spacing; scalar_t__* cs_offsets; scalar_t__* cs0_offsets; scalar_t__* reg_offsets; } ;
typedef  enum brcmnand_cs_reg { ____Placeholder_brcmnand_cs_reg } brcmnand_cs_reg ;

/* Variables and functions */
 size_t BRCMNAND_CS0_BASE ; 
 size_t BRCMNAND_CS1_BASE ; 

__attribute__((used)) static inline u16 brcmnand_cs_offset(struct brcmnand_controller *ctrl, int cs,
				     enum brcmnand_cs_reg reg)
{
	u16 offs_cs0 = ctrl->reg_offsets[BRCMNAND_CS0_BASE];
	u16 offs_cs1 = ctrl->reg_offsets[BRCMNAND_CS1_BASE];
	u8 cs_offs;

	if (cs == 0 && ctrl->cs0_offsets)
		cs_offs = ctrl->cs0_offsets[reg];
	else
		cs_offs = ctrl->cs_offsets[reg];

	if (cs && offs_cs1)
		return offs_cs1 + (cs - 1) * ctrl->reg_spacing + cs_offs;

	return offs_cs0 + cs * ctrl->reg_spacing + cs_offs;
}