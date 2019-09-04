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
struct TYPE_5__ {int /*<<< orphan*/  hdp_cntl; } ;
struct TYPE_6__ {TYPE_2__ r300; } ;
struct TYPE_4__ {int /*<<< orphan*/  installed; } ;
struct radeon_device {int flags; int /*<<< orphan*/  dev; TYPE_3__ config; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_HOST_PATH_CNTL ; 
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int r100_cp_init (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r100_irq_set (struct radeon_device*) ; 
 int r100_pci_gart_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_set_common_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  r300_mc_program (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_clock_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_cp_errata_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int radeon_ib_pool_init (struct radeon_device*) ; 
 int radeon_irq_kms_init (struct radeon_device*) ; 
 int radeon_wb_init (struct radeon_device*) ; 
 int rv370_pcie_gart_enable (struct radeon_device*) ; 

__attribute__((used)) static int r420_startup(struct radeon_device *rdev)
{
	int r;

	/* set common regs */
	r100_set_common_regs(rdev);
	/* program mc */
	r300_mc_program(rdev);
	/* Resume clock */
	r420_clock_resume(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	if (rdev->flags & RADEON_IS_PCIE) {
		r = rv370_pcie_gart_enable(rdev);
		if (r)
			return r;
	}
	if (rdev->flags & RADEON_IS_PCI) {
		r = r100_pci_gart_enable(rdev);
		if (r)
			return r;
	}
	r420_pipes_init(rdev);

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	if (r)
		return r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	/* Enable IRQ */
	if (!rdev->irq.installed) {
		r = radeon_irq_kms_init(rdev);
		if (r)
			return r;
	}

	r100_irq_set(rdev);
	rdev->config.r300.hdp_cntl = RREG32(RADEON_HOST_PATH_CNTL);
	/* 1M ring buffer */
	r = r100_cp_init(rdev, 1024 * 1024);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP (%d).\n", r);
		return r;
	}
	r420_cp_errata_init(rdev);

	r = radeon_ib_pool_init(rdev);
	if (r) {
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		return r;
	}

	return 0;
}