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
struct radeon_device {int flags; scalar_t__ family; int accel_working; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; scalar_t__ is_atom_bios; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ CHIP_R420 ; 
 int EINVAL ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0007C0_CP_STAT ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_cp_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_enable_bm (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_pci_gart_fini (struct radeon_device*) ; 
 int r100_pci_gart_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_restore_sanity (struct radeon_device*) ; 
 int /*<<< orphan*/  r300_mc_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_debugfs (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_set_reg_safe (struct radeon_device*) ; 
 int r420_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_agp_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_agp_fini (struct radeon_device*) ; 
 int radeon_agp_init (struct radeon_device*) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int radeon_atombios_init (struct radeon_device*) ; 
 int radeon_bo_init (struct radeon_device*) ; 
 int radeon_boot_test_post_card (struct radeon_device*) ; 
 int radeon_combios_init (struct radeon_device*) ; 
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

int r420_init(struct radeon_device *rdev)
{
	int r;

	/* Initialize scratch registers */
	radeon_scratch_init(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);
	/* TODO: disable VGA need to use VGA request */
	/* restore some register to sane defaults */
	r100_restore_sanity(rdev);
	/* BIOS*/
	if (!radeon_get_bios(rdev)) {
		if (ASIC_IS_AVIVO(rdev))
			return -EINVAL;
	}
	if (rdev->is_atom_bios) {
		r = radeon_atombios_init(rdev);
		if (r) {
			return r;
		}
	} else {
		r = radeon_combios_init(rdev);
		if (r) {
			return r;
		}
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
	r300_mc_init(rdev);
	r420_debugfs(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	if (r) {
		return r;
	}
	/* Memory manager */
	r = radeon_bo_init(rdev);
	if (r) {
		return r;
	}
	if (rdev->family == CHIP_R420)
		r100_enable_bm(rdev);

	if (rdev->flags & RADEON_IS_PCIE) {
		r = rv370_pcie_gart_init(rdev);
		if (r)
			return r;
	}
	if (rdev->flags & RADEON_IS_PCI) {
		r = r100_pci_gart_init(rdev);
		if (r)
			return r;
	}
	r420_set_reg_safe(rdev);

	/* Initialize power management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r420_startup(rdev);
	if (r) {
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		if (rdev->flags & RADEON_IS_PCIE)
			rv370_pcie_gart_fini(rdev);
		if (rdev->flags & RADEON_IS_PCI)
			r100_pci_gart_fini(rdev);
		radeon_agp_fini(rdev);
		rdev->accel_working = false;
	}
	return 0;
}