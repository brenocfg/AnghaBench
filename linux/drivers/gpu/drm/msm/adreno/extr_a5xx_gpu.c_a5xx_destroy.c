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
struct msm_gpu {int /*<<< orphan*/  aspace; int /*<<< orphan*/  name; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {scalar_t__ gpmu_bo; scalar_t__ pfp_bo; scalar_t__ pm4_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a5xx_preempt_fini (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_gpu_cleanup (struct adreno_gpu*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct a5xx_gpu*) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (scalar_t__,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void a5xx_destroy(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	DBG("%s", gpu->name);

	a5xx_preempt_fini(gpu);

	if (a5xx_gpu->pm4_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		drm_gem_object_put_unlocked(a5xx_gpu->pm4_bo);
	}

	if (a5xx_gpu->pfp_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		drm_gem_object_put_unlocked(a5xx_gpu->pfp_bo);
	}

	if (a5xx_gpu->gpmu_bo) {
		msm_gem_unpin_iova(a5xx_gpu->gpmu_bo, gpu->aspace);
		drm_gem_object_put_unlocked(a5xx_gpu->gpmu_bo);
	}

	adreno_gpu_cleanup(adreno_gpu);
	kfree(a5xx_gpu);
}