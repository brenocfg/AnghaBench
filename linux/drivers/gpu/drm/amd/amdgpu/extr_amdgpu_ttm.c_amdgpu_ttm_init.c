#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u64 ;
struct sysinfo {int mem_unit; scalar_t__ totalram; } ;
struct TYPE_12__ {int gds_size; int gws_size; int oa_size; } ;
struct TYPE_13__ {int no_retry; } ;
struct TYPE_11__ {int initialized; TYPE_6__ bdev; int /*<<< orphan*/  aper_base_kaddr; int /*<<< orphan*/  gtt_window_lock; } ;
struct TYPE_10__ {int real_vram_size; int visible_vram_size; int /*<<< orphan*/  mc_vram_size; int /*<<< orphan*/  stolen_size; int /*<<< orphan*/  aper_base; } ;
struct amdgpu_device {TYPE_5__ gds; TYPE_4__ mman; TYPE_3__ gmc; int /*<<< orphan*/  stolen_vga_memory; int /*<<< orphan*/  dev; TYPE_2__* ddev; } ;
struct TYPE_9__ {TYPE_1__* anon_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int AMDGPU_DEFAULT_GTT_SIZE_MB ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  AMDGPU_PL_GDS ; 
 int /*<<< orphan*/  AMDGPU_PL_GWS ; 
 int /*<<< orphan*/  AMDGPU_PL_OA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_driver ; 
 int amdgpu_gtt_size ; 
 int amdgpu_ttm_debugfs_init (struct amdgpu_device*) ; 
 int amdgpu_ttm_fw_reserve_vram_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_vis_vram_limit ; 
 int /*<<< orphan*/  dma_addressing_limited (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap_wc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int ttm_bo_device_init (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_init_mm (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int amdgpu_ttm_init(struct amdgpu_device *adev)
{
	uint64_t gtt_size;
	int r;
	u64 vis_vram_limit;
	void *stolen_vga_buf;

	mutex_init(&adev->mman.gtt_window_lock);

	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&adev->mman.bdev,
			       &amdgpu_bo_driver,
			       adev->ddev->anon_inode->i_mapping,
			       dma_addressing_limited(adev->dev));
	if (r) {
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		return r;
	}
	adev->mman.initialized = true;

	/* We opt to avoid OOM on system pages allocations */
	adev->mman.bdev.no_retry = true;

	/* Initialize VRAM pool with all of VRAM divided into pages */
	r = ttm_bo_init_mm(&adev->mman.bdev, TTM_PL_VRAM,
				adev->gmc.real_vram_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing VRAM heap.\n");
		return r;
	}

	/* Reduce size of CPU-visible VRAM if requested */
	vis_vram_limit = (u64)amdgpu_vis_vram_limit * 1024 * 1024;
	if (amdgpu_vis_vram_limit > 0 &&
	    vis_vram_limit <= adev->gmc.visible_vram_size)
		adev->gmc.visible_vram_size = vis_vram_limit;

	/* Change the size here instead of the init above so only lpfn is affected */
	amdgpu_ttm_set_buffer_funcs_status(adev, false);
#ifdef CONFIG_64BIT
	adev->mman.aper_base_kaddr = ioremap_wc(adev->gmc.aper_base,
						adev->gmc.visible_vram_size);
#endif

	/*
	 *The reserved vram for firmware must be pinned to the specified
	 *place on the VRAM, so reserve it early.
	 */
	r = amdgpu_ttm_fw_reserve_vram_init(adev);
	if (r) {
		return r;
	}

	/* allocate memory as required for VGA
	 * This is used for VGA emulation and pre-OS scanout buffers to
	 * avoid display artifacts while transitioning between pre-OS
	 * and driver.  */
	r = amdgpu_bo_create_kernel(adev, adev->gmc.stolen_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VRAM,
				    &adev->stolen_vga_memory,
				    NULL, &stolen_vga_buf);
	if (r)
		return r;
	DRM_INFO("amdgpu: %uM of VRAM memory ready\n",
		 (unsigned) (adev->gmc.real_vram_size / (1024 * 1024)));

	/* Compute GTT size, either bsaed on 3/4th the size of RAM size
	 * or whatever the user passed on module init */
	if (amdgpu_gtt_size == -1) {
		struct sysinfo si;

		si_meminfo(&si);
		gtt_size = min(max((AMDGPU_DEFAULT_GTT_SIZE_MB << 20),
			       adev->gmc.mc_vram_size),
			       ((uint64_t)si.totalram * si.mem_unit * 3/4));
	}
	else
		gtt_size = (uint64_t)amdgpu_gtt_size << 20;

	/* Initialize GTT memory pool */
	r = ttm_bo_init_mm(&adev->mman.bdev, TTM_PL_TT, gtt_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing GTT heap.\n");
		return r;
	}
	DRM_INFO("amdgpu: %uM of GTT memory ready.\n",
		 (unsigned)(gtt_size / (1024 * 1024)));

	/* Initialize various on-chip memory pools */
	r = ttm_bo_init_mm(&adev->mman.bdev, AMDGPU_PL_GDS,
			   adev->gds.gds_size);
	if (r) {
		DRM_ERROR("Failed initializing GDS heap.\n");
		return r;
	}

	r = ttm_bo_init_mm(&adev->mman.bdev, AMDGPU_PL_GWS,
			   adev->gds.gws_size);
	if (r) {
		DRM_ERROR("Failed initializing gws heap.\n");
		return r;
	}

	r = ttm_bo_init_mm(&adev->mman.bdev, AMDGPU_PL_OA,
			   adev->gds.oa_size);
	if (r) {
		DRM_ERROR("Failed initializing oa heap.\n");
		return r;
	}

	/* Register debugfs entries for amdgpu_ttm */
	r = amdgpu_ttm_debugfs_init(adev);
	if (r) {
		DRM_ERROR("Failed to init debugfs\n");
		return r;
	}
	return 0;
}