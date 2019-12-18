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
struct msm_gpu {int /*<<< orphan*/  aspace; int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_CAST (void*) ; 
 scalar_t__ IS_ERR (void*) ; 
 int MSM_BO_GPU_READONLY ; 
 int MSM_BO_UNCACHED ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 void* msm_gem_kernel_new_locked (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct drm_gem_object**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (struct drm_gem_object*) ; 

struct drm_gem_object *adreno_fw_create_bo(struct msm_gpu *gpu,
		const struct firmware *fw, u64 *iova)
{
	struct drm_gem_object *bo;
	void *ptr;

	ptr = msm_gem_kernel_new_locked(gpu->dev, fw->size - 4,
		MSM_BO_UNCACHED | MSM_BO_GPU_READONLY, gpu->aspace, &bo, iova);

	if (IS_ERR(ptr))
		return ERR_CAST(ptr);

	memcpy(ptr, &fw->data[4], fw->size - 4);

	msm_gem_put_vaddr(bo);

	return bo;
}