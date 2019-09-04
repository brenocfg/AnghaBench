#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  vram_base; } ;
struct TYPE_8__ {int mode_config_initialized; } ;
struct cirrus_device {TYPE_4__* dev; TYPE_2__ mc; TYPE_1__ mode_info; } ;
struct TYPE_10__ {int preferred_depth; scalar_t__ prefer_shadow; int /*<<< orphan*/  fb_base; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct TYPE_11__ {TYPE_3__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRRUS_MAX_FB_HEIGHT ; 
 int /*<<< orphan*/  CIRRUS_MAX_FB_WIDTH ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  cirrus_crtc_init (TYPE_4__*) ; 
 struct drm_encoder* cirrus_encoder_init (TYPE_4__*) ; 
 int cirrus_fbdev_init (struct cirrus_device*) ; 
 struct drm_connector* cirrus_vga_init (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_mode_config_init (TYPE_4__*) ; 

int cirrus_modeset_init(struct cirrus_device *cdev)
{
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	int ret;

	drm_mode_config_init(cdev->dev);
	cdev->mode_info.mode_config_initialized = true;

	cdev->dev->mode_config.max_width = CIRRUS_MAX_FB_WIDTH;
	cdev->dev->mode_config.max_height = CIRRUS_MAX_FB_HEIGHT;

	cdev->dev->mode_config.fb_base = cdev->mc.vram_base;
	cdev->dev->mode_config.preferred_depth = 24;
	/* don't prefer a shadow on virt GPU */
	cdev->dev->mode_config.prefer_shadow = 0;

	cirrus_crtc_init(cdev->dev);

	encoder = cirrus_encoder_init(cdev->dev);
	if (!encoder) {
		DRM_ERROR("cirrus_encoder_init failed\n");
		return -1;
	}

	connector = cirrus_vga_init(cdev->dev);
	if (!connector) {
		DRM_ERROR("cirrus_vga_init failed\n");
		return -1;
	}

	drm_connector_attach_encoder(connector, encoder);

	ret = cirrus_fbdev_init(cdev);
	if (ret) {
		DRM_ERROR("cirrus_fbdev_init failed\n");
		return ret;
	}

	return 0;
}