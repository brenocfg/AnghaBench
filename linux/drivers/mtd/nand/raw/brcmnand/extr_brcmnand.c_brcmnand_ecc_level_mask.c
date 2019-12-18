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
typedef  int u32 ;
struct brcmnand_controller {int nand_version; } ;

/* Variables and functions */
 int NAND_ACC_CONTROL_ECC_EXT_SHIFT ; 
 int NAND_ACC_CONTROL_ECC_SHIFT ; 

__attribute__((used)) static inline u32 brcmnand_ecc_level_mask(struct brcmnand_controller *ctrl)
{
	u32 mask = (ctrl->nand_version >= 0x0600) ? 0x1f : 0x0f;

	mask <<= NAND_ACC_CONTROL_ECC_SHIFT;

	/* v7.2 includes additional ECC levels */
	if (ctrl->nand_version >= 0x0702)
		mask |= 0x7 << NAND_ACC_CONTROL_ECC_EXT_SHIFT;

	return mask;
}