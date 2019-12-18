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
struct tps65217_bl {int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  tps; } ;
struct TYPE_2__ {int brightness; int state; scalar_t__ power; scalar_t__ fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int BL_CORE_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_WLEDCTRL2 ; 
 struct tps65217_bl* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps65217_bl_disable (struct tps65217_bl*) ; 
 int tps65217_bl_enable (struct tps65217_bl*) ; 
 int tps65217_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65217_bl_update_status(struct backlight_device *bl)
{
	struct tps65217_bl *tps65217_bl = bl_get_data(bl);
	int rc;
	int brightness = bl->props.brightness;

	if (bl->props.state & BL_CORE_SUSPENDED)
		brightness = 0;

	if ((bl->props.power != FB_BLANK_UNBLANK) ||
		(bl->props.fb_blank != FB_BLANK_UNBLANK))
		/* framebuffer in low power mode or blanking active */
		brightness = 0;

	if (brightness > 0) {
		rc = tps65217_reg_write(tps65217_bl->tps,
					TPS65217_REG_WLEDCTRL2,
					brightness - 1,
					TPS65217_PROTECT_NONE);
		if (rc) {
			dev_err(tps65217_bl->dev,
				"failed to set brightness level: %d\n", rc);
			return rc;
		}

		dev_dbg(tps65217_bl->dev, "brightness set to %d\n", brightness);

		if (!tps65217_bl->is_enabled)
			rc = tps65217_bl_enable(tps65217_bl);
	} else {
		rc = tps65217_bl_disable(tps65217_bl);
	}

	return rc;
}