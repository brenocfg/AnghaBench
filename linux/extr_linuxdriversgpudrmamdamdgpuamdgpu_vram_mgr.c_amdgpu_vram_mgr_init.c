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
struct ttm_mem_type_manager {struct amdgpu_vram_mgr* priv; } ;
struct amdgpu_vram_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct amdgpu_vram_mgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_vram_mgr_init(struct ttm_mem_type_manager *man,
				unsigned long p_size)
{
	struct amdgpu_vram_mgr *mgr;

	mgr = kzalloc(sizeof(*mgr), GFP_KERNEL);
	if (!mgr)
		return -ENOMEM;

	drm_mm_init(&mgr->mm, 0, p_size);
	spin_lock_init(&mgr->lock);
	man->priv = mgr;
	return 0;
}