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
struct sun4i_drv {int /*<<< orphan*/  tcon_list; int /*<<< orphan*/  engine_list; int /*<<< orphan*/  frontend_list; } ;
struct TYPE_2__ {int allow_fb_modifiers; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int irq_enabled; TYPE_1__ mode_config; int /*<<< orphan*/  dev; struct sun4i_drv* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 struct sun4i_drv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_conflicting_framebuffers (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int of_reserved_mem_device_init (struct device*) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 int /*<<< orphan*/  sun4i_drv_driver ; 
 int /*<<< orphan*/  sun4i_framebuffer_init (struct drm_device*) ; 

__attribute__((used)) static int sun4i_drv_bind(struct device *dev)
{
	struct drm_device *drm;
	struct sun4i_drv *drv;
	int ret;

	drm = drm_dev_alloc(&sun4i_drv_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	drv = devm_kzalloc(dev, sizeof(*drv), GFP_KERNEL);
	if (!drv) {
		ret = -ENOMEM;
		goto free_drm;
	}

	dev_set_drvdata(dev, drm);
	drm->dev_private = drv;
	INIT_LIST_HEAD(&drv->frontend_list);
	INIT_LIST_HEAD(&drv->engine_list);
	INIT_LIST_HEAD(&drv->tcon_list);

	ret = of_reserved_mem_device_init(dev);
	if (ret && ret != -ENODEV) {
		dev_err(drm->dev, "Couldn't claim our memory region\n");
		goto free_drm;
	}

	drm_mode_config_init(drm);
	drm->mode_config.allow_fb_modifiers = true;

	ret = component_bind_all(drm->dev, drm);
	if (ret) {
		dev_err(drm->dev, "Couldn't bind all pipelines components\n");
		goto cleanup_mode_config;
	}

	/* drm_vblank_init calls kcalloc, which can fail */
	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	if (ret)
		goto cleanup_mode_config;

	drm->irq_enabled = true;

	/* Remove early framebuffers (ie. simplefb) */
	drm_fb_helper_remove_conflicting_framebuffers(NULL, "sun4i-drm-fb", false);

	sun4i_framebuffer_init(drm);

	/* Enable connectors polling */
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto finish_poll;

	drm_fbdev_generic_setup(drm, 32);

	return 0;

finish_poll:
	drm_kms_helper_poll_fini(drm);
cleanup_mode_config:
	drm_mode_config_cleanup(drm);
	of_reserved_mem_device_release(dev);
free_drm:
	drm_dev_put(drm);
	return ret;
}