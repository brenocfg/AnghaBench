#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_4__ props; } ;
struct asus_wmi {TYPE_3__* driver; struct backlight_device* backlight_device; TYPE_1__* platform_device; } ;
struct TYPE_7__ {int panel_power; int /*<<< orphan*/  brightness; TYPE_2__* quirks; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ store_backlight_power; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int ENODEV ; 
 int FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  asus_wmi_bl_ops ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct asus_wmi*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int read_backlight_power (struct asus_wmi*) ; 
 int /*<<< orphan*/  read_brightness (struct backlight_device*) ; 
 int read_brightness_max (struct asus_wmi*) ; 

__attribute__((used)) static int asus_wmi_backlight_init(struct asus_wmi *asus)
{
	struct backlight_device *bd;
	struct backlight_properties props;
	int max;
	int power;

	max = read_brightness_max(asus);
	if (max < 0)
		return max;

	power = read_backlight_power(asus);
	if (power == -ENODEV)
		power = FB_BLANK_UNBLANK;
	else if (power < 0)
		return power;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max;
	bd = backlight_device_register(asus->driver->name,
				       &asus->platform_device->dev, asus,
				       &asus_wmi_bl_ops, &props);
	if (IS_ERR(bd)) {
		pr_err("Could not register backlight device\n");
		return PTR_ERR(bd);
	}

	asus->backlight_device = bd;

	if (asus->driver->quirks->store_backlight_power)
		asus->driver->panel_power = power;

	bd->props.brightness = read_brightness(bd);
	bd->props.power = power;
	backlight_update_status(bd);

	asus->driver->brightness = bd->props.brightness;

	return 0;
}