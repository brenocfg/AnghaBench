#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int flags; int accel_working; int /*<<< orphan*/  mc_fw; int /*<<< orphan*/  dev; TYPE_2__ ih; TYPE_3__* ring; int /*<<< orphan*/  rlc_fw; int /*<<< orphan*/  pfp_fw; int /*<<< orphan*/  me_fw; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; int /*<<< orphan*/  bios; int /*<<< orphan*/  is_atom_bios; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ring_obj; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_IGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evergreen_init_golden_registers (struct radeon_device*) ; 
 int evergreen_mc_init (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_pcie_gart_fini (struct radeon_device*) ; 
 int evergreen_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_uvd_init (struct radeon_device*) ; 
 int ni_init_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_dma_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_ih_ring_init (struct radeon_device*,int) ; 
 int r600_init_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_fini (struct radeon_device*) ; 
 int r600_pcie_gart_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_ring_init (struct radeon_device*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  r600_scratch_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r700_cp_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_agp_disable (struct radeon_device*) ; 
 int radeon_agp_init (struct radeon_device*) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int radeon_atombios_init (struct radeon_device*) ; 
 int radeon_bo_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_card_posted (struct radeon_device*) ; 
 int radeon_fence_driver_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_bios (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_clock_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_pool_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_rlc_fini (struct radeon_device*) ; 

int evergreen_init(struct radeon_device *rdev)
{
	int r;

	/* Read BIOS */
	if (!radeon_get_bios(rdev)) {
		if (ASIC_IS_AVIVO(rdev))
			return -EINVAL;
	}
	/* Must be an ATOMBIOS */
	if (!rdev->is_atom_bios) {
		dev_err(rdev->dev, "Expecting atombios for evergreen GPU\n");
		return -EINVAL;
	}
	r = radeon_atombios_init(rdev);
	if (r)
		return r;
	/* reset the asic, the gfx blocks are often in a bad state
	 * after the driver is unloaded or after a resume
	 */
	if (radeon_asic_reset(rdev))
		dev_warn(rdev->dev, "GPU reset failed !\n");
	/* Post card if necessary */
	if (!radeon_card_posted(rdev)) {
		if (!rdev->bios) {
			dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
			return -EINVAL;
		}
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	}
	/* init golden registers */
	evergreen_init_golden_registers(rdev);
	/* Initialize scratch registers */
	r600_scratch_init(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);
	/* Initialize clocks */
	radeon_get_clock_info(rdev->ddev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	if (r)
		return r;
	/* initialize AGP */
	if (rdev->flags & RADEON_IS_AGP) {
		r = radeon_agp_init(rdev);
		if (r)
			radeon_agp_disable(rdev);
	}
	/* initialize memory controller */
	r = evergreen_mc_init(rdev);
	if (r)
		return r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	if (r)
		return r;

	if (ASIC_IS_DCE5(rdev)) {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw || !rdev->mc_fw) {
			r = ni_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
	} else {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) {
			r = r600_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
	}

	/* Initialize power management */
	radeon_pm_init(rdev);

	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ring_obj = NULL;
	r600_ring_init(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX], 1024 * 1024);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].ring_obj = NULL;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX], 64 * 1024);

	evergreen_uvd_init(rdev);

	rdev->ih.ring_obj = NULL;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	if (r)
		return r;

	rdev->accel_working = true;
	r = evergreen_startup(rdev);
	if (r) {
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		r700_cp_fini(rdev);
		r600_dma_fini(rdev);
		r600_irq_fini(rdev);
		if (rdev->flags & RADEON_IS_IGP)
			sumo_rlc_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		evergreen_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	}

	/* Don't start up if the MC ucode is missing on BTC parts.
	 * The default clocks and voltages before the MC ucode
	 * is loaded are not suffient for advanced operations.
	 */
	if (ASIC_IS_DCE5(rdev)) {
		if (!rdev->mc_fw && !(rdev->flags & RADEON_IS_IGP)) {
			DRM_ERROR("radeon: MC ucode required for NI+.\n");
			return -EINVAL;
		}
	}

	return 0;
}