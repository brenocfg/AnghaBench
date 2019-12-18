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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_vram_mm_funcs {int dummy; } ;
struct drm_vram_mm {size_t vram_size; int /*<<< orphan*/  bdev; struct drm_vram_mm_funcs const* funcs; int /*<<< orphan*/  vram_base; } ;
struct drm_device {TYPE_1__* anon_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  bo_driver ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int drm_vram_mm_init(struct drm_vram_mm *vmm, struct drm_device *dev,
		     uint64_t vram_base, size_t vram_size,
		     const struct drm_vram_mm_funcs *funcs)
{
	int ret;

	vmm->vram_base = vram_base;
	vmm->vram_size = vram_size;
	vmm->funcs = funcs;

	ret = ttm_bo_device_init(&vmm->bdev, &bo_driver,
				 dev->anon_inode->i_mapping,
				 true);
	if (ret)
		return ret;

	ret = ttm_bo_init_mm(&vmm->bdev, TTM_PL_VRAM, vram_size >> PAGE_SHIFT);
	if (ret)
		return ret;

	return 0;
}