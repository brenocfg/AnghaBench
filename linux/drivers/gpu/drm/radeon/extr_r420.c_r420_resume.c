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
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int flags; int accel_working; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; scalar_t__ is_atom_bios; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0007C0_CP_STAT ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_pci_gart_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_clock_resume (struct radeon_device*) ; 
 int r420_startup (struct radeon_device*) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 
 int /*<<< orphan*/  rv370_pcie_gart_disable (struct radeon_device*) ; 

int r420_resume(struct radeon_device *rdev)
{
	int r;

	/* Make sur GART are not working */
	if (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	if (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	/* Resume clock before doing reset */
	r420_clock_resume(rdev);
	/* Reset gpu before posting otherwise ATOM will enter infinite loop */
	if (radeon_asic_reset(rdev)) {
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	}
	/* check if cards are posted or not */
	if (rdev->is_atom_bios) {
		atom_asic_init(rdev->mode_info.atom_context);
	} else {
		radeon_combios_asic_init(rdev->ddev);
	}
	/* Resume clock after posting */
	r420_clock_resume(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r420_startup(rdev);
	if (r) {
		rdev->accel_working = false;
	}
	return r;
}