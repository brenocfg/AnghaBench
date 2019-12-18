#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct msm_gpu {int needs_hw_init; TYPE_2__* pdev; TYPE_1__* funcs; int /*<<< orphan*/  aspace; } ;
struct msm_drm_private {struct msm_gpu* gpu; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct msm_drm_private* dev_private; } ;
struct adreno_gpu {int /*<<< orphan*/ ** fw; } ;
struct a5xx_gpu {int /*<<< orphan*/ * pfp_bo; int /*<<< orphan*/ * pm4_bo; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* recover ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 size_t ADRENO_FW_PFP ; 
 size_t ADRENO_FW_PM4 ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int
reset_set(void *data, u64 val)
{
	struct drm_device *dev = data;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_gpu *gpu = priv->gpu;
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	if (!capable(CAP_SYS_ADMIN))
		return -EINVAL;

	/* TODO do we care about trying to make sure the GPU is idle?
	 * Since this is just a debug feature limited to CAP_SYS_ADMIN,
	 * maybe it is fine to let the user keep both pieces if they
	 * try to reset an active GPU.
	 */

	mutex_lock(&dev->struct_mutex);

	release_firmware(adreno_gpu->fw[ADRENO_FW_PM4]);
	adreno_gpu->fw[ADRENO_FW_PM4] = NULL;

	release_firmware(adreno_gpu->fw[ADRENO_FW_PFP]);
	adreno_gpu->fw[ADRENO_FW_PFP] = NULL;

	if (a5xx_gpu->pm4_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->pm4_bo);
		a5xx_gpu->pm4_bo = NULL;
	}

	if (a5xx_gpu->pfp_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->pfp_bo);
		a5xx_gpu->pfp_bo = NULL;
	}

	gpu->needs_hw_init = true;

	pm_runtime_get_sync(&gpu->pdev->dev);
	gpu->funcs->recover(gpu);

	pm_runtime_put_sync(&gpu->pdev->dev);
	mutex_unlock(&dev->struct_mutex);

	return 0;
}