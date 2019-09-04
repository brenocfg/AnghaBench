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
struct vc4_dev {int /*<<< orphan*/  ctm_manager; int /*<<< orphan*/  ctm_state_lock; int /*<<< orphan*/  async_modeset; } ;
struct vc4_ctm_state {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int max_width; int max_height; int preferred_depth; int async_page_flip; int allow_fb_modifiers; scalar_t__ num_connector; int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int vblank_disable_immediate; TYPE_1__ mode_config; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_cma_fbdev_init (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_init (int /*<<< orphan*/ *) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct vc4_ctm_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_ctm_state_funcs ; 
 int /*<<< orphan*/  vc4_mode_funcs ; 

int vc4_kms_load(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_ctm_state *ctm_state;
	int ret;

	sema_init(&vc4->async_modeset, 1);

	/* Set support for vblank irq fast disable, before drm_vblank_init() */
	dev->vblank_disable_immediate = true;

	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	if (ret < 0) {
		dev_err(dev->dev, "failed to initialize vblank\n");
		return ret;
	}

	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;
	dev->mode_config.funcs = &vc4_mode_funcs;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.async_page_flip = true;
	dev->mode_config.allow_fb_modifiers = true;

	drm_modeset_lock_init(&vc4->ctm_state_lock);

	ctm_state = kzalloc(sizeof(*ctm_state), GFP_KERNEL);
	if (!ctm_state)
		return -ENOMEM;
	drm_atomic_private_obj_init(&vc4->ctm_manager, &ctm_state->base,
				    &vc4_ctm_state_funcs);

	drm_mode_config_reset(dev);

	if (dev->mode_config.num_connector)
		drm_fb_cma_fbdev_init(dev, 32, 0);

	drm_kms_helper_poll_init(dev);

	return 0;
}