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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int HAL_ATLANTIC_UTILS_CHIP_MIPS ; 
 int HAL_ATLANTIC_UTILS_CHIP_MPI_AQ ; 
 int HAL_ATLANTIC_UTILS_CHIP_REVISION_A0 ; 
 int HAL_ATLANTIC_UTILS_CHIP_REVISION_B0 ; 
 int HAL_ATLANTIC_UTILS_CHIP_REVISION_B1 ; 
 int HAL_ATLANTIC_UTILS_CHIP_RPF2 ; 
 int HAL_ATLANTIC_UTILS_CHIP_TPO2 ; 
 int hw_atl_reg_glb_mif_id_get (struct aq_hw_s*) ; 

void hw_atl_utils_hw_chip_features_init(struct aq_hw_s *self, u32 *p)
{
	u32 chip_features = 0U;
	u32 val = hw_atl_reg_glb_mif_id_get(self);
	u32 mif_rev = val & 0xFFU;

	if ((0xFU & mif_rev) == 1U) {
		chip_features |= HAL_ATLANTIC_UTILS_CHIP_REVISION_A0 |
			HAL_ATLANTIC_UTILS_CHIP_MPI_AQ |
			HAL_ATLANTIC_UTILS_CHIP_MIPS;
	} else if ((0xFU & mif_rev) == 2U) {
		chip_features |= HAL_ATLANTIC_UTILS_CHIP_REVISION_B0 |
			HAL_ATLANTIC_UTILS_CHIP_MPI_AQ |
			HAL_ATLANTIC_UTILS_CHIP_MIPS |
			HAL_ATLANTIC_UTILS_CHIP_TPO2 |
			HAL_ATLANTIC_UTILS_CHIP_RPF2;
	} else if ((0xFU & mif_rev) == 0xAU) {
		chip_features |= HAL_ATLANTIC_UTILS_CHIP_REVISION_B1 |
			HAL_ATLANTIC_UTILS_CHIP_MPI_AQ |
			HAL_ATLANTIC_UTILS_CHIP_MIPS |
			HAL_ATLANTIC_UTILS_CHIP_TPO2 |
			HAL_ATLANTIC_UTILS_CHIP_RPF2;
	}

	*p = chip_features;
}