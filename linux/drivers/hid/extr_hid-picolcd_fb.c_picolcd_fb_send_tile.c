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
typedef  int u8 ;
struct picolcd_data {int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  hdev; } ;
struct hid_report {int maxfield; int /*<<< orphan*/ * field; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int PICOLCD_FAILED ; 
 int /*<<< orphan*/  REPORT_LCD_CMD_DATA ; 
 int /*<<< orphan*/  REPORT_LCD_DATA ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (int /*<<< orphan*/ ,int,int) ; 
 struct hid_report* picolcd_out_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int picolcd_fb_send_tile(struct picolcd_data *data, u8 *vbitmap,
		int chip, int tile)
{
	struct hid_report *report1, *report2;
	unsigned long flags;
	u8 *tdata;
	int i;

	report1 = picolcd_out_report(REPORT_LCD_CMD_DATA, data->hdev);
	if (!report1 || report1->maxfield != 1)
		return -ENODEV;
	report2 = picolcd_out_report(REPORT_LCD_DATA, data->hdev);
	if (!report2 || report2->maxfield != 1)
		return -ENODEV;

	spin_lock_irqsave(&data->lock, flags);
	if ((data->status & PICOLCD_FAILED)) {
		spin_unlock_irqrestore(&data->lock, flags);
		return -ENODEV;
	}
	hid_set_field(report1->field[0],  0, chip << 2);
	hid_set_field(report1->field[0],  1, 0x02);
	hid_set_field(report1->field[0],  2, 0x00);
	hid_set_field(report1->field[0],  3, 0x00);
	hid_set_field(report1->field[0],  4, 0xb8 | tile);
	hid_set_field(report1->field[0],  5, 0x00);
	hid_set_field(report1->field[0],  6, 0x00);
	hid_set_field(report1->field[0],  7, 0x40);
	hid_set_field(report1->field[0],  8, 0x00);
	hid_set_field(report1->field[0],  9, 0x00);
	hid_set_field(report1->field[0], 10,   32);

	hid_set_field(report2->field[0],  0, (chip << 2) | 0x01);
	hid_set_field(report2->field[0],  1, 0x00);
	hid_set_field(report2->field[0],  2, 0x00);
	hid_set_field(report2->field[0],  3,   32);

	tdata = vbitmap + (tile * 4 + chip) * 64;
	for (i = 0; i < 64; i++)
		if (i < 32)
			hid_set_field(report1->field[0], 11 + i, tdata[i]);
		else
			hid_set_field(report2->field[0], 4 + i - 32, tdata[i]);

	hid_hw_request(data->hdev, report1, HID_REQ_SET_REPORT);
	hid_hw_request(data->hdev, report2, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	return 0;
}