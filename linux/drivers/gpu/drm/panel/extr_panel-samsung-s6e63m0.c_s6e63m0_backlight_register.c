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
struct s6e63m0 {int /*<<< orphan*/  bl_dev; struct device* dev; } ;
struct device {int dummy; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_BRIGHTNESS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_backlight_device_register (struct device*,char*,struct device*,struct s6e63m0*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  s6e63m0_backlight_ops ; 

__attribute__((used)) static int s6e63m0_backlight_register(struct s6e63m0 *ctx)
{
	struct backlight_properties props = {
		.type		= BACKLIGHT_RAW,
		.brightness	= MAX_BRIGHTNESS,
		.max_brightness = MAX_BRIGHTNESS
	};
	struct device *dev = ctx->dev;
	int ret = 0;

	ctx->bl_dev = devm_backlight_device_register(dev, "panel", dev, ctx,
						     &s6e63m0_backlight_ops,
						     &props);
	if (IS_ERR(ctx->bl_dev)) {
		ret = PTR_ERR(ctx->bl_dev);
		DRM_DEV_ERROR(dev, "error registering backlight device (%d)\n",
			      ret);
	}

	return ret;
}