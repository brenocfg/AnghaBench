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
struct TYPE_2__ {int preferred_depth; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; scalar_t__ min_height; scalar_t__ min_width; void* funcs; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct vbox_private {unsigned int num_crtcs; struct drm_device ddev; } ;
struct vbox_crtc {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct vbox_crtc*) ; 
 int PTR_ERR (struct vbox_crtc*) ; 
 int /*<<< orphan*/  VBE_DISPI_MAX_XRES ; 
 int /*<<< orphan*/  VBE_DISPI_MAX_YRES ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int vbox_connector_init (struct drm_device*,struct vbox_crtc*,struct drm_encoder*) ; 
 struct vbox_crtc* vbox_crtc_init (struct drm_device*,unsigned int) ; 
 struct drm_encoder* vbox_encoder_init (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  vbox_mode_funcs ; 

int vbox_mode_init(struct vbox_private *vbox)
{
	struct drm_device *dev = &vbox->ddev;
	struct drm_encoder *encoder;
	struct vbox_crtc *vbox_crtc;
	unsigned int i;
	int ret;

	drm_mode_config_init(dev);

	dev->mode_config.funcs = (void *)&vbox_mode_funcs;
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.max_width = VBE_DISPI_MAX_XRES;
	dev->mode_config.max_height = VBE_DISPI_MAX_YRES;

	for (i = 0; i < vbox->num_crtcs; ++i) {
		vbox_crtc = vbox_crtc_init(dev, i);
		if (IS_ERR(vbox_crtc)) {
			ret = PTR_ERR(vbox_crtc);
			goto err_drm_mode_cleanup;
		}
		encoder = vbox_encoder_init(dev, i);
		if (!encoder) {
			ret = -ENOMEM;
			goto err_drm_mode_cleanup;
		}
		ret = vbox_connector_init(dev, vbox_crtc, encoder);
		if (ret)
			goto err_drm_mode_cleanup;
	}

	drm_mode_config_reset(dev);
	return 0;

err_drm_mode_cleanup:
	drm_mode_config_cleanup(dev);
	return ret;
}