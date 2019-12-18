#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ideapad_private {struct backlight_device* blightdev; TYPE_2__* platform_device; TYPE_1__* adev; } ;
struct backlight_properties {unsigned long max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {unsigned long brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_3__ props; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int EIO ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  VPCCMD_R_BL ; 
 int /*<<< orphan*/  VPCCMD_R_BL_MAX ; 
 int /*<<< orphan*/  VPCCMD_R_BL_POWER ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ *,struct ideapad_private*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  ideapad_backlight_ops ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int ideapad_backlight_init(struct ideapad_private *priv)
{
	struct backlight_device *blightdev;
	struct backlight_properties props;
	unsigned long max, now, power;

	if (read_ec_data(priv->adev->handle, VPCCMD_R_BL_MAX, &max))
		return -EIO;
	if (read_ec_data(priv->adev->handle, VPCCMD_R_BL, &now))
		return -EIO;
	if (read_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &power))
		return -EIO;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.max_brightness = max;
	props.type = BACKLIGHT_PLATFORM;
	blightdev = backlight_device_register("ideapad",
					      &priv->platform_device->dev,
					      priv,
					      &ideapad_backlight_ops,
					      &props);
	if (IS_ERR(blightdev)) {
		pr_err("Could not register backlight device\n");
		return PTR_ERR(blightdev);
	}

	priv->blightdev = blightdev;
	blightdev->props.brightness = now;
	blightdev->props.power = power ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
	backlight_update_status(blightdev);

	return 0;
}