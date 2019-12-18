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
struct mx3fb_data {struct backlight_device* bl; int /*<<< orphan*/  dev; int /*<<< orphan*/  backlight_level; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; void* fb_blank; void* power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 void* FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ ,struct mx3fb_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mx3fb_bl_get_brightness (struct backlight_device*) ; 
 int /*<<< orphan*/  mx3fb_lcdc_bl_ops ; 
 int /*<<< orphan*/  sdc_set_brightness (struct mx3fb_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mx3fb_init_backlight(struct mx3fb_data *fbd)
{
	struct backlight_properties props;
	struct backlight_device	*bl;

	if (fbd->bl)
		return;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.max_brightness = 0xff;
	props.type = BACKLIGHT_RAW;
	sdc_set_brightness(fbd, fbd->backlight_level);

	bl = backlight_device_register("mx3fb-bl", fbd->dev, fbd,
				       &mx3fb_lcdc_bl_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(fbd->dev, "error %ld on backlight register\n",
				PTR_ERR(bl));
		return;
	}

	fbd->bl = bl;
	bl->props.power = FB_BLANK_UNBLANK;
	bl->props.fb_blank = FB_BLANK_UNBLANK;
	bl->props.brightness = mx3fb_bl_get_brightness(bl);
}