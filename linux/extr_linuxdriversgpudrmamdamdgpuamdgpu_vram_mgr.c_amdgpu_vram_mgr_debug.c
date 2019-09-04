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
struct ttm_mem_type_manager {int /*<<< orphan*/  size; struct amdgpu_vram_mgr* priv; } ;
struct drm_printer {int dummy; } ;
struct amdgpu_vram_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int amdgpu_vram_mgr_usage (struct ttm_mem_type_manager*) ; 
 int amdgpu_vram_mgr_vis_usage (struct ttm_mem_type_manager*) ; 
 int /*<<< orphan*/  drm_mm_print (int /*<<< orphan*/ *,struct drm_printer*) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vram_mgr_debug(struct ttm_mem_type_manager *man,
				  struct drm_printer *printer)
{
	struct amdgpu_vram_mgr *mgr = man->priv;

	spin_lock(&mgr->lock);
	drm_mm_print(&mgr->mm, printer);
	spin_unlock(&mgr->lock);

	drm_printf(printer, "man size:%llu pages, ram usage:%lluMB, vis usage:%lluMB\n",
		   man->size, amdgpu_vram_mgr_usage(man) >> 20,
		   amdgpu_vram_mgr_vis_usage(man) >> 20);
}