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
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct file {int dummy; } ;
struct drm_vram_mm {TYPE_1__* funcs; } ;
struct TYPE_2__ {int (* verify_access ) (struct ttm_buffer_object*,struct file*) ;} ;

/* Variables and functions */
 struct drm_vram_mm* drm_vram_mm_of_bdev (int /*<<< orphan*/ ) ; 
 int stub1 (struct ttm_buffer_object*,struct file*) ; 

__attribute__((used)) static int bo_driver_verify_access(struct ttm_buffer_object *bo,
				   struct file *filp)
{
	struct drm_vram_mm *vmm = drm_vram_mm_of_bdev(bo->bdev);

	if (!vmm->funcs || !vmm->funcs->verify_access)
		return 0;
	return vmm->funcs->verify_access(bo, filp);
}