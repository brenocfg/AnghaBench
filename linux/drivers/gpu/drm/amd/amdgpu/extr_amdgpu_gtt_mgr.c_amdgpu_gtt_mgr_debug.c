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
typedef  int /*<<< orphan*/  u64 ;
struct ttm_mem_type_manager {int /*<<< orphan*/  size; struct amdgpu_gtt_mgr* priv; } ;
struct drm_printer {int dummy; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  available; int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int amdgpu_gtt_mgr_usage (struct ttm_mem_type_manager*) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_print (int /*<<< orphan*/ *,struct drm_printer*) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_gtt_mgr_debug(struct ttm_mem_type_manager *man,
				 struct drm_printer *printer)
{
	struct amdgpu_gtt_mgr *mgr = man->priv;

	spin_lock(&mgr->lock);
	drm_mm_print(&mgr->mm, printer);
	spin_unlock(&mgr->lock);

	drm_printf(printer, "man size:%llu pages, gtt available:%lld pages, usage:%lluMB\n",
		   man->size, (u64)atomic64_read(&mgr->available),
		   amdgpu_gtt_mgr_usage(man) >> 20);
}