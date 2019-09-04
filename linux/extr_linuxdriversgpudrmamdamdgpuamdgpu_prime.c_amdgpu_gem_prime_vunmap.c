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
struct drm_gem_object {int dummy; } ;
struct amdgpu_bo {int /*<<< orphan*/  dma_buf_vmap; } ;

/* Variables and functions */
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 

void amdgpu_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	ttm_bo_kunmap(&bo->dma_buf_vmap);
}