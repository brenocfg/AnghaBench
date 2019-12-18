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
struct etnaviv_gpu {int /*<<< orphan*/  cooling; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  fence_event; int /*<<< orphan*/  sync_point_work; int /*<<< orphan*/  fence_spinlock; int /*<<< orphan*/  fence_idr; int /*<<< orphan*/  fence_context; struct drm_device* drm; } ;
struct etnaviv_drm_private {int /*<<< orphan*/  num_gpus; struct etnaviv_gpu** gpu; } ;
struct drm_device {struct etnaviv_drm_private* dev_private; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_ETNAVIV_THERMAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cooling_ops ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct etnaviv_gpu* dev_get_drvdata (struct device*) ; 
 scalar_t__ dev_name (struct device*) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int etnaviv_gpu_clk_enable (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_sched_fini (struct etnaviv_gpu*) ; 
 int etnaviv_sched_init (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_point_worker ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_of_cooling_device_register (int /*<<< orphan*/ ,char*,struct etnaviv_gpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etnaviv_gpu_bind(struct device *dev, struct device *master,
	void *data)
{
	struct drm_device *drm = data;
	struct etnaviv_drm_private *priv = drm->dev_private;
	struct etnaviv_gpu *gpu = dev_get_drvdata(dev);
	int ret;

	if (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL)) {
		gpu->cooling = thermal_of_cooling_device_register(dev->of_node,
				(char *)dev_name(dev), gpu, &cooling_ops);
		if (IS_ERR(gpu->cooling))
			return PTR_ERR(gpu->cooling);
	}

	gpu->wq = alloc_ordered_workqueue(dev_name(dev), 0);
	if (!gpu->wq) {
		ret = -ENOMEM;
		goto out_thermal;
	}

	ret = etnaviv_sched_init(gpu);
	if (ret)
		goto out_workqueue;

#ifdef CONFIG_PM
	ret = pm_runtime_get_sync(gpu->dev);
#else
	ret = etnaviv_gpu_clk_enable(gpu);
#endif
	if (ret < 0)
		goto out_sched;


	gpu->drm = drm;
	gpu->fence_context = dma_fence_context_alloc(1);
	idr_init(&gpu->fence_idr);
	spin_lock_init(&gpu->fence_spinlock);

	INIT_WORK(&gpu->sync_point_work, sync_point_worker);
	init_waitqueue_head(&gpu->fence_event);

	priv->gpu[priv->num_gpus++] = gpu;

	pm_runtime_mark_last_busy(gpu->dev);
	pm_runtime_put_autosuspend(gpu->dev);

	return 0;

out_sched:
	etnaviv_sched_fini(gpu);

out_workqueue:
	destroy_workqueue(gpu->wq);

out_thermal:
	if (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL))
		thermal_cooling_device_unregister(gpu->cooling);

	return ret;
}