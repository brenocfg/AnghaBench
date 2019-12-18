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
struct radeon_device {int flags; int accel_working; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; scalar_t__ bios; scalar_t__ is_atom_bios; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0007C0_CP_STAT ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_cp_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_restore_sanity (struct radeon_device*) ; 
 int /*<<< orphan*/  r520_mc_init (struct radeon_device*) ; 
 int r520_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_agp_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_agp_fini (struct radeon_device*) ; 
 int radeon_agp_init (struct radeon_device*) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int radeon_atombios_init (struct radeon_device*) ; 
 int radeon_bo_init (struct radeon_device*) ; 
 int radeon_boot_test_post_card (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_card_posted (struct radeon_device*) ; 
 int radeon_fence_driver_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_bios (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_clock_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_pool_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_scratch_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  rv370_pcie_gart_fini (struct radeon_device*) ; 
 int rv370_pcie_gart_init (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_debugfs (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_set_safe_registers (struct radeon_device*) ; 

int r520_init(struct radeon_device *rdev)
{
	int r;

	/* Initialize scratch registers */
	radeon_scratch_init(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);
	/* restore some register to sane defaults */
	r100_restore_sanity(rdev);
	/* TODO: disable VGA need to use VGA request */
	/* BIOS*/
	if (!radeon_get_bios(rdev)) {
		if (ASIC_IS_AVIVO(rdev))
			return -EINVAL;
	}
	if (rdev->is_atom_bios) {
		r = radeon_atombios_init(rdev);
		if (r)
			return r;
	} else {
		dev_err(rdev->dev, "Expecting atombios for RV515 GPU\n");
		return -EINVAL;
	}
	/* Reset gpu before posting otherwise ATOM will enter infinite loop */
	if (radeon_asic_reset(rdev)) {
		dev_warn(rdev->dev,
			"GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	}
	/* check if cards are posted or not */
	if (radeon_boot_test_post_card(rdev) == false)
		return -EINVAL;

	if (!radeon_card_posted(rdev) && rdev->bios) {
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	}
	/* Initialize clocks */
	radeon_get_clock_info(rdev->ddev);
	/* initialize AGP */
	if (rdev->flags & RADEON_IS_AGP) {
		r = radeon_agp_init(rdev);
		if (r) {
			radeon_agp_disable(rdev);
		}
	}
	/* initialize memory controller */
	r520_mc_init(rdev);
	rv515_debugfs(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	if (r)
		return r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	if (r)
		return r;
	r = rv370_pcie_gart_init(rdev);
	if (r)
		return r;
	rv515_set_safe_registers(rdev);

	/* Initialize power management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r520_startup(rdev);
	if (r) {
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		rv370_pcie_gart_fini(rdev);
		radeon_agp_fini(rdev);
		rdev->accel_working = false;
	}
	return 0;
}