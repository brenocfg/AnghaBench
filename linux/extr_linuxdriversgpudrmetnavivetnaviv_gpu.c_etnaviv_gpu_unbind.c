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
struct TYPE_2__ {scalar_t__ suballoc; } ;
struct etnaviv_gpu {int /*<<< orphan*/ * cooling; int /*<<< orphan*/  fence_idr; int /*<<< orphan*/ * drm; int /*<<< orphan*/ * mmu; int /*<<< orphan*/ * cmdbuf_suballoc; TYPE_1__ buffer; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_ETNAVIV_THERMAL ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct etnaviv_gpu* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_suballoc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_gpu_hw_suspend (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_iommu_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_sched_fini (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void etnaviv_gpu_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct etnaviv_gpu *gpu = dev_get_drvdata(dev);

	DBG("%s", dev_name(gpu->dev));

	flush_workqueue(gpu->wq);
	destroy_workqueue(gpu->wq);

	etnaviv_sched_fini(gpu);

#ifdef CONFIG_PM
	pm_runtime_get_sync(gpu->dev);
	pm_runtime_put_sync_suspend(gpu->dev);
#else
	etnaviv_gpu_hw_suspend(gpu);
#endif

	if (gpu->buffer.suballoc)
		etnaviv_cmdbuf_free(&gpu->buffer);

	if (gpu->cmdbuf_suballoc) {
		etnaviv_cmdbuf_suballoc_destroy(gpu->cmdbuf_suballoc);
		gpu->cmdbuf_suballoc = NULL;
	}

	if (gpu->mmu) {
		etnaviv_iommu_destroy(gpu->mmu);
		gpu->mmu = NULL;
	}

	gpu->drm = NULL;
	idr_destroy(&gpu->fence_idr);

	if (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL))
		thermal_cooling_device_unregister(gpu->cooling);
	gpu->cooling = NULL;
}