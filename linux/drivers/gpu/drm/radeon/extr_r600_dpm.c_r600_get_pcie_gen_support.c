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
struct radeon_device {int dummy; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;

/* Variables and functions */
#define  RADEON_PCIE_GEN1 130 
#define  RADEON_PCIE_GEN2 129 
#define  RADEON_PCIE_GEN3 128 
 int RADEON_PCIE_SPEED_50 ; 
 int RADEON_PCIE_SPEED_80 ; 

enum radeon_pcie_gen r600_get_pcie_gen_support(struct radeon_device *rdev,
					       u32 sys_mask,
					       enum radeon_pcie_gen asic_gen,
					       enum radeon_pcie_gen default_gen)
{
	switch (asic_gen) {
	case RADEON_PCIE_GEN1:
		return RADEON_PCIE_GEN1;
	case RADEON_PCIE_GEN2:
		return RADEON_PCIE_GEN2;
	case RADEON_PCIE_GEN3:
		return RADEON_PCIE_GEN3;
	default:
		if ((sys_mask & RADEON_PCIE_SPEED_80) && (default_gen == RADEON_PCIE_GEN3))
			return RADEON_PCIE_GEN3;
		else if ((sys_mask & RADEON_PCIE_SPEED_50) && (default_gen == RADEON_PCIE_GEN2))
			return RADEON_PCIE_GEN2;
		else
			return RADEON_PCIE_GEN1;
	}
	return RADEON_PCIE_GEN1;
}