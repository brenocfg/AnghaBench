#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct msm_mdss {TYPE_4__* funcs; } ;
struct msm_kms {TYPE_2__* funcs; } ;
struct TYPE_7__ {scalar_t__ paddr; int /*<<< orphan*/  size; int /*<<< orphan*/  mm; } ;
struct msm_drm_private {int num_crtcs; int /*<<< orphan*/  wq; TYPE_3__ vram; scalar_t__ fbdev; TYPE_1__* event_thread; struct msm_mdss* mdss; struct msm_kms* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; scalar_t__ registered; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* destroy ) (struct drm_device*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (struct msm_kms*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * thread; int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 unsigned long DMA_ATTR_NO_KERNEL_MAPPING ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 scalar_t__ fbdev ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msm_drm_private*) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_fbdev_free (struct drm_device*) ; 
 int /*<<< orphan*/  msm_gem_shrinker_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  msm_perf_debugfs_cleanup (struct msm_drm_private*) ; 
 int /*<<< orphan*/  msm_rd_debugfs_cleanup (struct msm_drm_private*) ; 
 struct drm_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int msm_drm_uninit(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *ddev = platform_get_drvdata(pdev);
	struct msm_drm_private *priv = ddev->dev_private;
	struct msm_kms *kms = priv->kms;
	struct msm_mdss *mdss = priv->mdss;
	int i;

	/*
	 * Shutdown the hw if we're far enough along where things might be on.
	 * If we run this too early, we'll end up panicking in any variety of
	 * places. Since we don't register the drm device until late in
	 * msm_drm_init, drm_dev->registered is used as an indicator that the
	 * shutdown will be successful.
	 */
	if (ddev->registered) {
		drm_dev_unregister(ddev);
		drm_atomic_helper_shutdown(ddev);
	}

	/* We must cancel and cleanup any pending vblank enable/disable
	 * work before drm_irq_uninstall() to avoid work re-enabling an
	 * irq after uninstall has disabled it.
	 */

	flush_workqueue(priv->wq);

	/* clean up event worker threads */
	for (i = 0; i < priv->num_crtcs; i++) {
		if (priv->event_thread[i].thread) {
			kthread_destroy_worker(&priv->event_thread[i].worker);
			priv->event_thread[i].thread = NULL;
		}
	}

	msm_gem_shrinker_cleanup(ddev);

	drm_kms_helper_poll_fini(ddev);

	msm_perf_debugfs_cleanup(priv);
	msm_rd_debugfs_cleanup(priv);

#ifdef CONFIG_DRM_FBDEV_EMULATION
	if (fbdev && priv->fbdev)
		msm_fbdev_free(ddev);
#endif

	drm_mode_config_cleanup(ddev);

	pm_runtime_get_sync(dev);
	drm_irq_uninstall(ddev);
	pm_runtime_put_sync(dev);

	if (kms && kms->funcs)
		kms->funcs->destroy(kms);

	if (priv->vram.paddr) {
		unsigned long attrs = DMA_ATTR_NO_KERNEL_MAPPING;
		drm_mm_takedown(&priv->vram.mm);
		dma_free_attrs(dev, priv->vram.size, NULL,
			       priv->vram.paddr, attrs);
	}

	component_unbind_all(dev, ddev);

	if (mdss && mdss->funcs)
		mdss->funcs->destroy(ddev);

	ddev->dev_private = NULL;
	drm_dev_put(ddev);

	destroy_workqueue(priv->wq);
	kfree(priv);

	return 0;
}