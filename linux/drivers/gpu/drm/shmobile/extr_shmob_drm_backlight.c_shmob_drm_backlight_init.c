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
struct shmob_drm_device {TYPE_1__* pdata; } ;
struct drm_connector {struct drm_device* dev; } ;
struct shmob_drm_connector {struct backlight_device* backlight; struct drm_connector connector; } ;
struct shmob_drm_backlight_data {scalar_t__ max_brightness; int /*<<< orphan*/  name; } ;
struct drm_device {int /*<<< orphan*/  dev; struct shmob_drm_device* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; scalar_t__ brightness; scalar_t__ max_brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {struct shmob_drm_backlight_data backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct shmob_drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  shmob_drm_backlight_ops ; 

int shmob_drm_backlight_init(struct shmob_drm_connector *scon)
{
	struct shmob_drm_device *sdev = scon->connector.dev->dev_private;
	const struct shmob_drm_backlight_data *bdata = &sdev->pdata->backlight;
	struct drm_connector *connector = &scon->connector;
	struct drm_device *dev = connector->dev;
	struct backlight_device *backlight;

	if (!bdata->max_brightness)
		return 0;

	backlight = backlight_device_register(bdata->name, dev->dev, scon,
					      &shmob_drm_backlight_ops, NULL);
	if (IS_ERR(backlight)) {
		dev_err(dev->dev, "unable to register backlight device: %ld\n",
			PTR_ERR(backlight));
		return PTR_ERR(backlight);
	}

	backlight->props.max_brightness = bdata->max_brightness;
	backlight->props.brightness = bdata->max_brightness;
	backlight->props.power = FB_BLANK_POWERDOWN;
	backlight_update_status(backlight);

	scon->backlight = backlight;
	return 0;
}