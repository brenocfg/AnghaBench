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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_gpu {TYPE_1__* funcs; } ;
struct msm_drm_private {struct platform_device* gpu_pdev; } ;
struct drm_device {int /*<<< orphan*/  render; int /*<<< orphan*/  primary; int /*<<< orphan*/  dev; int /*<<< orphan*/  struct_mutex; struct msm_drm_private* dev_private; } ;
struct adreno_gpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* debugfs_init ) (struct msm_gpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int adreno_load_fw (struct adreno_gpu*) ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ ,char*) ; 
 int msm_gpu_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gpu* platform_get_drvdata (struct platform_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

struct msm_gpu *adreno_load_gpu(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = priv->gpu_pdev;
	struct msm_gpu *gpu = NULL;
	struct adreno_gpu *adreno_gpu;
	int ret;

	if (pdev)
		gpu = platform_get_drvdata(pdev);

	if (!gpu) {
		dev_err_once(dev->dev, "no GPU device was found\n");
		return NULL;
	}

	adreno_gpu = to_adreno_gpu(gpu);

	/*
	 * The number one reason for HW init to fail is if the firmware isn't
	 * loaded yet. Try that first and don't bother continuing on
	 * otherwise
	 */

	ret = adreno_load_fw(adreno_gpu);
	if (ret)
		return NULL;

	/* Make sure pm runtime is active and reset any previous errors */
	pm_runtime_set_active(&pdev->dev);

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		pm_runtime_put_sync(&pdev->dev);
		DRM_DEV_ERROR(dev->dev, "Couldn't power up the GPU: %d\n", ret);
		return NULL;
	}

	mutex_lock(&dev->struct_mutex);
	ret = msm_gpu_hw_init(gpu);
	mutex_unlock(&dev->struct_mutex);
	pm_runtime_put_autosuspend(&pdev->dev);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "gpu hw init failed: %d\n", ret);
		return NULL;
	}

#ifdef CONFIG_DEBUG_FS
	if (gpu->funcs->debugfs_init) {
		gpu->funcs->debugfs_init(gpu, dev->primary);
		gpu->funcs->debugfs_init(gpu, dev->render);
	}
#endif

	return gpu;
}