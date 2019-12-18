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
struct picolcd_data {int lcd_contrast; struct lcd_device* lcd; TYPE_1__* hdev; } ;
struct TYPE_6__ {int max_contrast; } ;
struct lcd_device {TYPE_3__ props; } ;
struct hid_report {int maxfield; TYPE_2__** field; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int report_count; int report_size; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct lcd_device* lcd_device_register (int /*<<< orphan*/ ,struct device*,struct picolcd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picolcd_lcdops ; 
 int /*<<< orphan*/  picolcd_set_contrast (struct lcd_device*,int) ; 

int picolcd_init_lcd(struct picolcd_data *data, struct hid_report *report)
{
	struct device *dev = &data->hdev->dev;
	struct lcd_device *ldev;

	if (!report)
		return -ENODEV;
	if (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) {
		dev_err(dev, "unsupported CONTRAST report");
		return -EINVAL;
	}

	ldev = lcd_device_register(dev_name(dev), dev, data, &picolcd_lcdops);
	if (IS_ERR(ldev)) {
		dev_err(dev, "failed to register LCD\n");
		return PTR_ERR(ldev);
	}
	ldev->props.max_contrast = 0x0ff;
	data->lcd_contrast = 0xe5;
	data->lcd = ldev;
	picolcd_set_contrast(ldev, 0xe5);
	return 0;
}