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
struct picolcd_data {int lcd_brightness; struct backlight_device* backlight; TYPE_1__* hdev; } ;
struct hid_report {int maxfield; TYPE_2__** field; } ;
struct device {int dummy; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int brightness; } ;
struct backlight_device {TYPE_3__ props; } ;
typedef  int /*<<< orphan*/  props ;
struct TYPE_5__ {int report_count; int report_size; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,struct device*,struct picolcd_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  picolcd_blops ; 
 int /*<<< orphan*/  picolcd_set_brightness (struct backlight_device*) ; 

int picolcd_init_backlight(struct picolcd_data *data, struct hid_report *report)
{
	struct device *dev = &data->hdev->dev;
	struct backlight_device *bdev;
	struct backlight_properties props;
	if (!report)
		return -ENODEV;
	if (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) {
		dev_err(dev, "unsupported BRIGHTNESS report");
		return -EINVAL;
	}

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	bdev = backlight_device_register(dev_name(dev), dev, data,
			&picolcd_blops, &props);
	if (IS_ERR(bdev)) {
		dev_err(dev, "failed to register backlight\n");
		return PTR_ERR(bdev);
	}
	bdev->props.brightness     = 0xff;
	data->lcd_brightness       = 0xff;
	data->backlight            = bdev;
	picolcd_set_brightness(bdev);
	return 0;
}