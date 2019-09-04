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
struct picolcd_data {int opmode_delay; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  hdev; } ;
struct hid_report {int maxfield; int /*<<< orphan*/ * field; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int PICOLCD_BOOTLOADER ; 
 int /*<<< orphan*/  REPORT_EXIT_FLASHER ; 
 int /*<<< orphan*/  REPORT_EXIT_KEYBOARD ; 
 struct picolcd_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (int /*<<< orphan*/ ,int,int) ; 
 struct hid_report* picolcd_out_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static ssize_t picolcd_operation_mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct picolcd_data *data = dev_get_drvdata(dev);
	struct hid_report *report = NULL;
	size_t cnt = count;
	int timeout = data->opmode_delay;
	unsigned long flags;

	if (cnt >= 3 && strncmp("lcd", buf, 3) == 0) {
		if (data->status & PICOLCD_BOOTLOADER)
			report = picolcd_out_report(REPORT_EXIT_FLASHER, data->hdev);
		buf += 3;
		cnt -= 3;
	} else if (cnt >= 10 && strncmp("bootloader", buf, 10) == 0) {
		if (!(data->status & PICOLCD_BOOTLOADER))
			report = picolcd_out_report(REPORT_EXIT_KEYBOARD, data->hdev);
		buf += 10;
		cnt -= 10;
	}
	if (!report || report->maxfield != 1)
		return -EINVAL;

	while (cnt > 0 && (buf[cnt-1] == '\n' || buf[cnt-1] == '\r'))
		cnt--;
	if (cnt != 0)
		return -EINVAL;

	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, timeout & 0xff);
	hid_set_field(report->field[0], 1, (timeout >> 8) & 0xff);
	hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	return count;
}