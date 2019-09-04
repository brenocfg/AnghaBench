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
struct picolcd_data {int lcd_brightness; scalar_t__ lcd_power; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  hdev; } ;
struct hid_report {int maxfield; TYPE_2__** field; } ;
struct TYPE_3__ {int brightness; scalar_t__ power; } ;
struct backlight_device {TYPE_1__ props; } ;
struct TYPE_4__ {int report_count; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int PICOLCD_FAILED ; 
 int /*<<< orphan*/  REPORT_BRIGHTNESS ; 
 struct picolcd_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct hid_report* picolcd_out_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int picolcd_set_brightness(struct backlight_device *bdev)
{
	struct picolcd_data *data = bl_get_data(bdev);
	struct hid_report *report = picolcd_out_report(REPORT_BRIGHTNESS, data->hdev);
	unsigned long flags;

	if (!report || report->maxfield != 1 || report->field[0]->report_count != 1)
		return -ENODEV;

	data->lcd_brightness = bdev->props.brightness & 0x0ff;
	data->lcd_power      = bdev->props.power;
	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, data->lcd_power == FB_BLANK_UNBLANK ? data->lcd_brightness : 0);
	if (!(data->status & PICOLCD_FAILED))
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	return 0;
}