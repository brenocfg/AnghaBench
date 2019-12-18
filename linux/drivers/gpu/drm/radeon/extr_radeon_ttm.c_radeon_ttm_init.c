#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int real_vram_size; int gtt_size; int /*<<< orphan*/  visible_vram_size; } ;
struct TYPE_9__ {int initialized; int /*<<< orphan*/  bdev; } ;
struct radeon_device {TYPE_5__ mc; TYPE_4__ mman; int /*<<< orphan*/  stolen_vga_memory; TYPE_3__* pdev; TYPE_2__* ddev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* anon_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  dma_addressing_limited (int /*<<< orphan*/ *) ; 
 int radeon_bo_create (struct radeon_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_driver ; 
 int radeon_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 int radeon_ttm_debugfs_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int radeon_ttm_init(struct radeon_device *rdev)
{
	int r;

	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&rdev->mman.bdev,
			       &radeon_bo_driver,
			       rdev->ddev->anon_inode->i_mapping,
			       dma_addressing_limited(&rdev->pdev->dev));
	if (r) {
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		return r;
	}
	rdev->mman.initialized = true;
	r = ttm_bo_init_mm(&rdev->mman.bdev, TTM_PL_VRAM,
				rdev->mc.real_vram_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing VRAM heap.\n");
		return r;
	}
	/* Change the size here instead of the init above so only lpfn is affected */
	radeon_ttm_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	r = radeon_bo_create(rdev, 256 * 1024, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, NULL,
			     NULL, &rdev->stolen_vga_memory);
	if (r) {
		return r;
	}
	r = radeon_bo_reserve(rdev->stolen_vga_memory, false);
	if (r)
		return r;
	r = radeon_bo_pin(rdev->stolen_vga_memory, RADEON_GEM_DOMAIN_VRAM, NULL);
	radeon_bo_unreserve(rdev->stolen_vga_memory);
	if (r) {
		radeon_bo_unref(&rdev->stolen_vga_memory);
		return r;
	}
	DRM_INFO("radeon: %uM of VRAM memory ready\n",
		 (unsigned) (rdev->mc.real_vram_size / (1024 * 1024)));
	r = ttm_bo_init_mm(&rdev->mman.bdev, TTM_PL_TT,
				rdev->mc.gtt_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing GTT heap.\n");
		return r;
	}
	DRM_INFO("radeon: %uM of GTT memory ready.\n",
		 (unsigned)(rdev->mc.gtt_size / (1024 * 1024)));

	r = radeon_ttm_debugfs_init(rdev);
	if (r) {
		DRM_ERROR("Failed to init debugfs\n");
		return r;
	}
	return 0;
}