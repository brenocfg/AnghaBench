#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int sched_priority; } ;
struct platform_device {int dummy; } ;
struct msm_mdss {TYPE_1__* funcs; } ;
struct TYPE_12__ {int normalize_zpos; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; } ;
struct msm_kms {int /*<<< orphan*/  irq; TYPE_4__ mode_config; TYPE_3__* funcs; struct msm_drm_private* dev_private; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  event_list; } ;
struct msm_drm_private {int num_crtcs; TYPE_8__* event_thread; TYPE_5__* disp_thread; TYPE_7__** crtcs; struct msm_kms* kms; TYPE_2__ vblank_ctrl; int /*<<< orphan*/  inactive_list; int /*<<< orphan*/  wq; struct msm_mdss* mdss; struct msm_kms* dev; } ;
struct drm_driver {int dummy; } ;
struct drm_device {int /*<<< orphan*/  irq; TYPE_4__ mode_config; TYPE_3__* funcs; struct msm_drm_private* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_16__ {struct msm_kms* thread; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  worker; struct msm_kms* dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_15__ {TYPE_6__ base; } ;
struct TYPE_13__ {struct msm_kms* thread; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  worker; struct msm_kms* dev; } ;
struct TYPE_11__ {int (* hw_init ) (struct msm_kms*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* destroy ) (struct msm_kms*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 struct msm_kms* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct msm_kms*) ; 
#define  KMS_DPU 130 
#define  KMS_MDP4 129 
#define  KMS_MDP5 128 
 int PTR_ERR (struct msm_kms*) ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int component_bind_all (struct device*,struct msm_kms*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct msm_kms* dpu_kms_init (struct msm_kms*) ; 
 int dpu_mdss_init (struct msm_kms*) ; 
 struct msm_kms* drm_dev_alloc (struct drm_driver*,struct device*) ; 
 int drm_dev_register (struct msm_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_unref (struct msm_kms*) ; 
 int drm_irq_install (struct msm_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct msm_kms*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct msm_kms*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct msm_kms*) ; 
 int drm_vblank_init (struct msm_kms*,int) ; 
 int get_mdp_ver (struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct msm_drm_private*) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 void* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (struct msm_kms*) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 
 struct msm_drm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct msm_kms* mdp4_kms_init (struct msm_kms*) ; 
 struct msm_kms* mdp5_kms_init (struct msm_kms*) ; 
 int mdp5_mdss_init (struct msm_kms*) ; 
 int /*<<< orphan*/  mode_config_funcs ; 
 int /*<<< orphan*/  mode_config_helper_funcs ; 
 int msm_debugfs_late_init (struct msm_kms*) ; 
 int /*<<< orphan*/  msm_drm_uninit (struct device*) ; 
 int /*<<< orphan*/  msm_gem_shrinker_init (struct msm_kms*) ; 
 int msm_init_vram (struct msm_kms*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_kms*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sched_setscheduler (struct msm_kms*,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vblank_ctrl_worker ; 

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
		dev_err(dev, "failed to allocate drm_device\n");
		return PTR_ERR(ddev);
	}

	platform_set_drvdata(pdev, ddev);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		ret = -ENOMEM;
		goto err_unref_drm_dev;
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

	INIT_LIST_HEAD(&priv->inactive_list);
	INIT_LIST_HEAD(&priv->vblank_ctrl.event_list);
	kthread_init_work(&priv->vblank_ctrl.work, vblank_ctrl_worker);
	spin_lock_init(&priv->vblank_ctrl.lock);

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
		kms = ERR_PTR(-ENODEV);
		break;
	}

	if (IS_ERR(kms)) {
		/*
		 * NOTE: once we have GPU support, having no kms should not
		 * be considered fatal.. ideally we would still support gpu
		 * and (for example) use dmabuf/prime to share buffers with
		 * imx drm driver on iMX5
		 */
		dev_err(dev, "failed to load kms\n");
		ret = PTR_ERR(kms);
		goto err_msm_uninit;
	}

	/* Enable normalization of plane zpos */
	ddev->mode_config.normalize_zpos = true;

	if (kms) {
		ret = kms->funcs->hw_init(kms);
		if (ret) {
			dev_err(dev, "kms hw init failed: %d\n", ret);
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

		/* initialize display thread */
		priv->disp_thread[i].crtc_id = priv->crtcs[i]->base.id;
		kthread_init_worker(&priv->disp_thread[i].worker);
		priv->disp_thread[i].dev = ddev;
		priv->disp_thread[i].thread =
			kthread_run(kthread_worker_fn,
				&priv->disp_thread[i].worker,
				"crtc_commit:%d", priv->disp_thread[i].crtc_id);
		ret = sched_setscheduler(priv->disp_thread[i].thread,
							SCHED_FIFO, &param);
		if (ret)
			pr_warn("display thread priority update failed: %d\n",
									ret);

		if (IS_ERR(priv->disp_thread[i].thread)) {
			dev_err(dev, "failed to create crtc_commit kthread\n");
			priv->disp_thread[i].thread = NULL;
		}

		/* initialize event thread */
		priv->event_thread[i].crtc_id = priv->crtcs[i]->base.id;
		kthread_init_worker(&priv->event_thread[i].worker);
		priv->event_thread[i].dev = ddev;
		priv->event_thread[i].thread =
			kthread_run(kthread_worker_fn,
				&priv->event_thread[i].worker,
				"crtc_event:%d", priv->event_thread[i].crtc_id);
		/**
		 * event thread should also run at same priority as disp_thread
		 * because it is handling frame_done events. A lower priority
		 * event thread and higher priority disp_thread can causes
		 * frame_pending counters beyond 2. This can lead to commit
		 * failure at crtc commit level.
		 */
		ret = sched_setscheduler(priv->event_thread[i].thread,
							SCHED_FIFO, &param);
		if (ret)
			pr_warn("display event thread priority update failed: %d\n",
									ret);

		if (IS_ERR(priv->event_thread[i].thread)) {
			dev_err(dev, "failed to create crtc_event kthread\n");
			priv->event_thread[i].thread = NULL;
		}

		if ((!priv->disp_thread[i].thread) ||
				!priv->event_thread[i].thread) {
			/* clean up previously created threads if any */
			for ( ; i >= 0; i--) {
				if (priv->disp_thread[i].thread) {
					kthread_stop(
						priv->disp_thread[i].thread);
					priv->disp_thread[i].thread = NULL;
				}

				if (priv->event_thread[i].thread) {
					kthread_stop(
						priv->event_thread[i].thread);
					priv->event_thread[i].thread = NULL;
				}
			}
			goto err_msm_uninit;
		}
	}

	ret = drm_vblank_init(ddev, priv->num_crtcs);
	if (ret < 0) {
		dev_err(dev, "failed to initialize vblank\n");
		goto err_msm_uninit;
	}

	if (kms) {
		pm_runtime_get_sync(dev);
		ret = drm_irq_install(ddev, kms->irq);
		pm_runtime_put_sync(dev);
		if (ret < 0) {
			dev_err(dev, "failed to install IRQ handler\n");
			goto err_msm_uninit;
		}
	}

	ret = drm_dev_register(ddev, 0);
	if (ret)
		goto err_msm_uninit;

	drm_mode_config_reset(ddev);

#ifdef CONFIG_DRM_FBDEV_EMULATION
	if (fbdev)
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
err_unref_drm_dev:
	drm_dev_unref(ddev);
	return ret;
}