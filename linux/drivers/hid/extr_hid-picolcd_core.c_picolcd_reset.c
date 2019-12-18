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
struct picolcd_data {int status; int /*<<< orphan*/  lock; } ;
struct hid_report {int maxfield; int /*<<< orphan*/ * field; } ;
struct hid_device {scalar_t__ product; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int PICOLCD_BOOTLOADER ; 
 int PICOLCD_FAILED ; 
 int /*<<< orphan*/  REPORT_RESET ; 
 scalar_t__ USB_DEVICE_ID_PICOLCD_BOOTLOADER ; 
 struct picolcd_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int picolcd_check_version (struct hid_device*) ; 
 int /*<<< orphan*/  picolcd_fb_refresh (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_leds_set (struct picolcd_data*) ; 
 struct hid_report* picolcd_out_report (int /*<<< orphan*/ ,struct hid_device*) ; 
 int /*<<< orphan*/  picolcd_resume_backlight (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_resume_lcd (struct picolcd_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int picolcd_reset(struct hid_device *hdev)
{
	struct picolcd_data *data = hid_get_drvdata(hdev);
	struct hid_report *report = picolcd_out_report(REPORT_RESET, hdev);
	unsigned long flags;
	int error;

	if (!data || !report || report->maxfield != 1)
		return -ENODEV;

	spin_lock_irqsave(&data->lock, flags);
	if (hdev->product == USB_DEVICE_ID_PICOLCD_BOOTLOADER)
		data->status |= PICOLCD_BOOTLOADER;

	/* perform the reset */
	hid_set_field(report->field[0], 0, 1);
	if (data->status & PICOLCD_FAILED) {
		spin_unlock_irqrestore(&data->lock, flags);
		return -ENODEV;
	}
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);

	error = picolcd_check_version(hdev);
	if (error)
		return error;

	picolcd_resume_lcd(data);
	picolcd_resume_backlight(data);
	picolcd_fb_refresh(data);
	picolcd_leds_set(data);
	return 0;
}