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
struct TYPE_2__ {int flags; } ;
struct rv6xx_ps {TYPE_1__ low; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 int /*<<< orphan*/  r600_enable_dynamic_pcie_gen2 (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_bif_dynamic_pcie_gen2 (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_pcie_gen2_support (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_force_pcie_gen1 (struct radeon_device*) ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv6xx_enable_dynamic_pcie_gen2(struct radeon_device *rdev,
					   struct radeon_ps *new_ps,
					   bool enable)
{
	struct rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	if (enable) {
		rv6xx_enable_bif_dynamic_pcie_gen2(rdev, true);
		rv6xx_enable_pcie_gen2_support(rdev);
		r600_enable_dynamic_pcie_gen2(rdev, true);
	} else {
		if (!(new_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2))
			rv6xx_force_pcie_gen1(rdev);
		rv6xx_enable_bif_dynamic_pcie_gen2(rdev, false);
		r600_enable_dynamic_pcie_gen2(rdev, false);
	}
}