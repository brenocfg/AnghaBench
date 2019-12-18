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
struct picolcd_data {int lcd_contrast; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  hdev; } ;
struct lcd_device {int dummy; } ;
struct hid_report {int maxfield; TYPE_1__** field; } ;
struct TYPE_2__ {int report_count; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int PICOLCD_FAILED ; 
 int /*<<< orphan*/  REPORT_CONTRAST ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct picolcd_data* lcd_get_data (struct lcd_device*) ; 
 struct hid_report* picolcd_out_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int picolcd_set_contrast(struct lcd_device *ldev, int contrast)
{
	struct picolcd_data *data = lcd_get_data(ldev);
	struct hid_report *report = picolcd_out_report(REPORT_CONTRAST, data->hdev);
	unsigned long flags;

	if (!report || report->maxfield != 1 || report->field[0]->report_count != 1)
		return -ENODEV;

	data->lcd_contrast = contrast & 0x0ff;
	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, data->lcd_contrast);
	if (!(data->status & PICOLCD_FAILED))
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	return 0;
}