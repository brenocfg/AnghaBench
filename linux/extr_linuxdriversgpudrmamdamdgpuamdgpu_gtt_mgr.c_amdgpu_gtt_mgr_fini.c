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
struct ttm_mem_type_manager {struct amdgpu_gtt_mgr* priv; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_gtt_mgr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_gtt_mgr_fini(struct ttm_mem_type_manager *man)
{
	struct amdgpu_gtt_mgr *mgr = man->priv;
	spin_lock(&mgr->lock);
	drm_mm_takedown(&mgr->mm);
	spin_unlock(&mgr->lock);
	kfree(mgr);
	man->priv = NULL;
	return 0;
}