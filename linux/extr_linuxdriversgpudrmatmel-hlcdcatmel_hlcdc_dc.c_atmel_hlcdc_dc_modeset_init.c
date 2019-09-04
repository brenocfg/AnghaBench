#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct drm_device {TYPE_2__ mode_config; int /*<<< orphan*/  dev; struct atmel_hlcdc_dc* dev_private; } ;
struct atmel_hlcdc_dc {TYPE_1__* desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;

/* Variables and functions */
 int atmel_hlcdc_create_outputs (struct drm_device*) ; 
 int atmel_hlcdc_create_planes (struct drm_device*) ; 
 int atmel_hlcdc_crtc_create (struct drm_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  mode_config_funcs ; 

__attribute__((used)) static int atmel_hlcdc_dc_modeset_init(struct drm_device *dev)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	int ret;

	drm_mode_config_init(dev);

	ret = atmel_hlcdc_create_outputs(dev);
	if (ret) {
		dev_err(dev->dev, "failed to create HLCDC outputs: %d\n", ret);
		return ret;
	}

	ret = atmel_hlcdc_create_planes(dev);
	if (ret) {
		dev_err(dev->dev, "failed to create planes: %d\n", ret);
		return ret;
	}

	ret = atmel_hlcdc_crtc_create(dev);
	if (ret) {
		dev_err(dev->dev, "failed to create crtc\n");
		return ret;
	}

	dev->mode_config.min_width = dc->desc->min_width;
	dev->mode_config.min_height = dc->desc->min_height;
	dev->mode_config.max_width = dc->desc->max_width;
	dev->mode_config.max_height = dc->desc->max_height;
	dev->mode_config.funcs = &mode_config_funcs;

	return 0;
}