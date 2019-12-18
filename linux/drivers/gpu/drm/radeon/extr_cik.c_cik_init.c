#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/  doorbell_index; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int flags; int accel_working; int /*<<< orphan*/  mc_fw; int /*<<< orphan*/  dev; TYPE_2__ ih; struct radeon_ring* ring; int /*<<< orphan*/  rlc_fw; int /*<<< orphan*/  sdma_fw; int /*<<< orphan*/  mec_fw; int /*<<< orphan*/  ce_fw; int /*<<< orphan*/  pfp_fw; int /*<<< orphan*/  me_fw; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; int /*<<< orphan*/  bios; int /*<<< orphan*/  is_atom_bios; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int RADEON_IS_IGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_cp_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_init_golden_registers (struct radeon_device*) ; 
 int cik_init_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_irq_fini (struct radeon_device*) ; 
 int cik_mc_init (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_mec_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_pcie_gart_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_scratch_init (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_sdma_fini (struct radeon_device*) ; 
 int cik_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_uvd_init (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_vce_init (struct radeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r600_ih_ring_init (struct radeon_device*,int) ; 
 int r600_pcie_gart_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_ring_init (struct radeon_device*,struct radeon_ring*,int) ; 
 int radeon_atombios_init (struct radeon_device*) ; 
 int radeon_bo_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_card_posted (struct radeon_device*) ; 
 int radeon_doorbell_get (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int radeon_fence_driver_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_bios (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_get_clock_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_pool_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vm_manager_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_rlc_fini (struct radeon_device*) ; 

int cik_init(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	int r;

	/* Read BIOS */
	if (!radeon_get_bios(rdev)) {
		if (ASIC_IS_AVIVO(rdev))
			return -EINVAL;
	}
	/* Must be an ATOMBIOS */
	if (!rdev->is_atom_bios) {
		dev_err(rdev->dev, "Expecting atombios for cayman GPU\n");
		return -EINVAL;
	}
	r = radeon_atombios_init(rdev);
	if (r)
		return r;

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
	cik_init_golden_registers(rdev);
	/* Initialize scratch registers */
	cik_scratch_init(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);
	/* Initialize clocks */
	radeon_get_clock_info(rdev->ddev);

	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	if (r)
		return r;

	/* initialize memory controller */
	r = cik_mc_init(rdev);
	if (r)
		return r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	if (r)
		return r;

	if (rdev->flags & RADEON_IS_IGP) {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw ||
		    !rdev->mec_fw || !rdev->sdma_fw || !rdev->rlc_fw) {
			r = cik_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
	} else {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw ||
		    !rdev->mec_fw || !rdev->sdma_fw || !rdev->rlc_fw ||
		    !rdev->mc_fw) {
			r = cik_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
	}

	/* Initialize power management */
	radeon_pm_init(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	ring->ring_obj = NULL;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	ring->ring_obj = NULL;
	r600_ring_init(rdev, ring, 1024 * 1024);
	r = radeon_doorbell_get(rdev, &ring->doorbell_index);
	if (r)
		return r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	ring->ring_obj = NULL;
	r600_ring_init(rdev, ring, 1024 * 1024);
	r = radeon_doorbell_get(rdev, &ring->doorbell_index);
	if (r)
		return r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	ring->ring_obj = NULL;
	r600_ring_init(rdev, ring, 256 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	ring->ring_obj = NULL;
	r600_ring_init(rdev, ring, 256 * 1024);

	cik_uvd_init(rdev);
	cik_vce_init(rdev);

	rdev->ih.ring_obj = NULL;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	if (r)
		return r;

	rdev->accel_working = true;
	r = cik_startup(rdev);
	if (r) {
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		cik_cp_fini(rdev);
		cik_sdma_fini(rdev);
		cik_irq_fini(rdev);
		sumo_rlc_fini(rdev);
		cik_mec_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_vm_manager_fini(rdev);
		radeon_irq_kms_fini(rdev);
		cik_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	}

	/* Don't start up if the MC ucode is missing.
	 * The default clocks and voltages before the MC ucode
	 * is loaded are not suffient for advanced operations.
	 */
	if (!rdev->mc_fw && !(rdev->flags & RADEON_IS_IGP)) {
		DRM_ERROR("radeon: MC ucode required for NI+.\n");
		return -EINVAL;
	}

	return 0;
}