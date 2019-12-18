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
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  OT_EC_BL_BRIGHTNESS_MAX ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  get_backlight_brightness (struct backlight_device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 struct backlight_device* oaktrail_bl_device ; 
 int /*<<< orphan*/  oaktrail_bl_ops ; 
 TYPE_2__* oaktrail_device ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int oaktrail_backlight_init(void)
{
	struct backlight_device *bd;
	struct backlight_properties props;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = OT_EC_BL_BRIGHTNESS_MAX;
	bd = backlight_device_register(DRIVER_NAME,
				       &oaktrail_device->dev, NULL,
				       &oaktrail_bl_ops,
				       &props);

	if (IS_ERR(bd)) {
		oaktrail_bl_device = NULL;
		pr_warning("Unable to register backlight device\n");
		return PTR_ERR(bd);
	}

	oaktrail_bl_device = bd;

	bd->props.brightness = get_backlight_brightness(bd);
	bd->props.power = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	return 0;
}