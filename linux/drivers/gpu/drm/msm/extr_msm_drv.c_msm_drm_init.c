#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int sched_priority; } ;
struct platform_device {int dummy; } ;
struct msm_mdss {TYPE_6__* funcs; } ;
struct TYPE_8__ {int normalize_zpos; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; } ;
struct msm_kms {int /*<<< orphan*/  irq; TYPE_2__ mode_config; TYPE_1__* funcs; struct msm_kms* dev; struct msm_drm_private* dev_private; } ;
struct msm_drm_private {int num_crtcs; int /*<<< orphan*/  fbdev; TYPE_5__* event_thread; TYPE_4__** crtcs; struct msm_kms* kms; int /*<<< orphan*/  inactive_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_work; int /*<<< orphan*/  wq; struct msm_mdss* mdss; struct msm_kms* dev; } ;
struct drm_driver {int dummy; } ;
struct drm_device {int /*<<< orphan*/  irq; TYPE_2__ mode_config; TYPE_1__* funcs; struct drm_device* dev; struct msm_drm_private* dev_private; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* destroy ) (struct msm_kms*) ;} ;
struct TYPE_11__ {struct msm_kms* thread; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  worker; struct msm_kms* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct TYPE_7__ {int (* hw_init ) (struct msm_kms*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct msm_kms*) ; 
#define  KMS_DPU 130 
#define  KMS_MDP4 129 
#define  KMS_MDP5 128 
 int PTR_ERR (struct msm_kms*) ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int component_bind_all (struct device*,struct msm_kms*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct msm_kms* dpu_kms_init (struct msm_kms*) ; 
 int dpu_mdss_init (struct msm_kms*) ; 
 struct msm_kms* drm_dev_alloc (struct drm_driver*,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct msm_kms*) ; 
 int drm_dev_register (struct msm_kms*,int /*<<< orphan*/ ) ; 
 int drm_irq_install (struct msm_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct msm_kms*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct msm_kms*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct msm_kms*) ; 
 int drm_vblank_init (struct msm_kms*,int) ; 
 scalar_t__ fbdev ; 
 int get_mdp_ver (struct platform_device*) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct msm_drm_private*) ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 struct msm_kms* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 
 struct msm_drm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct msm_kms* mdp4_kms_init (struct msm_kms*) ; 
 struct msm_kms* mdp5_kms_init (struct msm_kms*) ; 
 int mdp5_mdss_init (struct msm_kms*) ; 
 int /*<<< orphan*/  mode_config_funcs ; 
 int /*<<< orphan*/  mode_config_helper_funcs ; 
 int msm_debugfs_late_init (struct msm_kms*) ; 
 int /*<<< orphan*/  msm_drm_uninit (struct device*) ; 
 int /*<<< orphan*/  msm_fbdev_init (struct msm_kms*) ; 
 int /*<<< orphan*/  msm_gem_free_work ; 
 int /*<<< orphan*/  msm_gem_shrinker_init (struct msm_kms*) ; 
 int msm_init_vram (struct msm_kms*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_kms*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int sched_setscheduler (struct msm_kms*,int /*<<< orphan*/ ,struct sched_param*) ; 
 int stub1 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int msm_drm_init(struct device *dev, struct drm_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *ddev;
	struct msm_drm_private *priv;
	struct msm_kms *kms;
	struct msm_mdss *mdss;
	int ret, i;
	struct sched_param param;

	ddev = drm_dev_alloc(drv, dev);
	if (IS_ERR(ddev)) {
		DRM_DEV_ERROR(dev, "failed to allocate drm_device\n");
		return PTR_ERR(ddev);
	}

	platform_set_drvdata(pdev, ddev);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		ret = -ENOMEM;
		goto err_put_drm_dev;
	}

	ddev->dev_private = priv;
	priv->dev = ddev;

	switch (get_mdp_ver(pdev)) {
	case KMS_MDP5:
		ret = mdp5_mdss_init(ddev);
		break;
	case KMS_DPU:
		ret = dpu_mdss_init(ddev);
		break;
	default:
		ret = 0;
		break;
	}
	if (ret)
		goto err_free_priv;

	mdss = priv->mdss;

	priv->wq = alloc_ordered_workqueue("msm", 0);

	INIT_WORK(&priv->free_work, msm_gem_free_work);
	init_llist_head(&priv->free_list);

	INIT_LIST_HEAD(&priv->inactive_list);

	drm_mode_config_init(ddev);

	/* Bind all our sub-components: */
	ret = component_bind_all(dev, ddev);
	if (ret)
		goto err_destroy_mdss;

	ret = msm_init_vram(ddev);
	if (ret)
		goto err_msm_uninit;

	msm_gem_shrinker_init(ddev);

	switch (get_mdp_ver(pdev)) {
	case KMS_MDP4:
		kms = mdp4_kms_init(ddev);
		priv->kms = kms;
		break;
	case KMS_MDP5:
		kms = mdp5_kms_init(ddev);
		break;
	case KMS_DPU:
		kms = dpu_kms_init(ddev);
		priv->kms = kms;
		break;
	default:
		/* valid only for the dummy headless case, where of_node=NULL */
		WARN_ON(dev->of_node);
		kms = NULL;
		break;
	}

	if (IS_ERR(kms)) {
		DRM_DEV_ERROR(dev, "failed to load kms\n");
		ret = PTR_ERR(kms);
		priv->kms = NULL;
		goto err_msm_uninit;
	}

	/* Enable normalization of plane zpos */
	ddev->mode_config.normalize_zpos = true;

	if (kms) {
		kms->dev = ddev;
		ret = kms->funcs->hw_init(kms);
		if (ret) {
			DRM_DEV_ERROR(dev, "kms hw init failed: %d\n", ret);
			goto err_msm_uninit;
		}
	}

	ddev->mode_config.funcs = &mode_config_funcs;
	ddev->mode_config.helper_private = &mode_config_helper_funcs;

	/**
	 * this priority was found during empiric testing to have appropriate
	 * realtime scheduling to process display updates and interact with
	 * other real time and normal priority task
	 */
	param.sched_priority = 16;
	for (i = 0; i < priv->num_crtcs; i++) {
		/* initialize event thread */
		priv->event_thread[i].crtc_id = priv->crtcs[i]->base.id;
		kthread_init_worker(&priv->event_thread[i].worker);
		priv->event_thread[i].dev = ddev;
		priv->event_thread[i].thread =
			kthread_run(kthread_worker_fn,
				&priv->event_thread[i].worker,
				"crtc_event:%d", priv->event_thread[i].crtc_id);
		if (IS_ERR(priv->event_thread[i].thread)) {
			DRM_DEV_ERROR(dev, "failed to create crtc_event kthread\n");
			priv->event_thread[i].thread = NULL;
			goto err_msm_uninit;
		}

		ret = sched_setscheduler(priv->event_thread[i].thread,
					 SCHED_FIFO, &param);
		if (ret)
			dev_warn(dev, "event_thread set priority failed:%d\n",
				 ret);
	}

	ret = drm_vblank_init(ddev, priv->num_crtcs);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "failed to initialize vblank\n");
		goto err_msm_uninit;
	}

	if (kms) {
		pm_runtime_get_sync(dev);
		ret = drm_irq_install(ddev, kms->irq);
		pm_runtime_put_sync(dev);
		if (ret < 0) {
			DRM_DEV_ERROR(dev, "failed to install IRQ handler\n");
			goto err_msm_uninit;
		}
	}

	ret = drm_dev_register(ddev, 0);
	if (ret)
		goto err_msm_uninit;

	drm_mode_config_reset(ddev);

#ifdef CONFIG_DRM_FBDEV_EMULATION
	if (kms && fbdev)
		priv->fbdev = msm_fbdev_init(ddev);
#endif

	ret = msm_debugfs_late_init(ddev);
	if (ret)
		goto err_msm_uninit;

	drm_kms_helper_poll_init(ddev);

	return 0;

err_msm_uninit:
	msm_drm_uninit(dev);
	return ret;
err_destroy_mdss:
	if (mdss && mdss->funcs)
		mdss->funcs->destroy(ddev);
err_free_priv:
	kfree(priv);
err_put_drm_dev:
	drm_dev_put(ddev);
	return ret;
}