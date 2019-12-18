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
typedef  size_t u8 ;
struct picolcd_data {int /*<<< orphan*/  addr_sz; } ;
struct hid_report {int id; } ;
struct hid_device {int /*<<< orphan*/  debug_wait; int /*<<< orphan*/  debug_list; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  BUFF_SZ ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  REPORT_BL_ERASE_MEMORY 139 
#define  REPORT_BL_READ_MEMORY 138 
#define  REPORT_BL_WRITE_MEMORY 137 
#define  REPORT_DEVID 136 
#define  REPORT_EE_DATA 135 
#define  REPORT_ERROR_CODE 134 
#define  REPORT_HOOK_VERSION 133 
#define  REPORT_IR_DATA 132 
#define  REPORT_KEY_STATE 131 
#define  REPORT_MEMORY 130 
#define  REPORT_SPLASH_SIZE 129 
#define  REPORT_VERSION 128 
 int /*<<< orphan*/  dump_buff_as_hex (char*,int /*<<< orphan*/ ,size_t*,size_t) ; 
 char** error_codes ; 
 int /*<<< orphan*/  hid_debug_event (struct hid_device*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void picolcd_debug_raw_event(struct picolcd_data *data,
		struct hid_device *hdev, struct hid_report *report,
		u8 *raw_data, int size)
{
	char *buff;

#define BUFF_SZ 256
	/* Avoid unnecessary overhead if debugfs is disabled */
	if (list_empty(&hdev->debug_list))
		return;

	buff = kmalloc(BUFF_SZ, GFP_ATOMIC);
	if (!buff)
		return;

	switch (report->id) {
	case REPORT_ERROR_CODE:
		/* 2 data bytes with affected report and error code */
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_ERROR_CODE", report->id, size-1);
		hid_debug_event(hdev, buff);
		if (raw_data[2] < ARRAY_SIZE(error_codes))
			snprintf(buff, BUFF_SZ, "\tError code 0x%02x (%s) in reply to report 0x%02x\n",
					raw_data[2], error_codes[raw_data[2]], raw_data[1]);
		else
			snprintf(buff, BUFF_SZ, "\tError code 0x%02x in reply to report 0x%02x\n",
					raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		break;
	case REPORT_KEY_STATE:
		/* 2 data bytes with key state */
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_KEY_STATE", report->id, size-1);
		hid_debug_event(hdev, buff);
		if (raw_data[1] == 0)
			snprintf(buff, BUFF_SZ, "\tNo key pressed\n");
		else if (raw_data[2] == 0)
			snprintf(buff, BUFF_SZ, "\tOne key pressed: 0x%02x (%d)\n",
					raw_data[1], raw_data[1]);
		else
			snprintf(buff, BUFF_SZ, "\tTwo keys pressed: 0x%02x (%d), 0x%02x (%d)\n",
					raw_data[1], raw_data[1], raw_data[2], raw_data[2]);
		hid_debug_event(hdev, buff);
		break;
	case REPORT_IR_DATA:
		/* Up to 20 byes of IR scancode data */
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_IR_DATA", report->id, size-1);
		hid_debug_event(hdev, buff);
		if (raw_data[1] == 0) {
			snprintf(buff, BUFF_SZ, "\tUnexpectedly 0 data length\n");
			hid_debug_event(hdev, buff);
		} else if (raw_data[1] + 1 <= size) {
			snprintf(buff, BUFF_SZ, "\tData length: %d\n\tIR Data: ",
					raw_data[1]);
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, raw_data+2, raw_data[1]);
			hid_debug_event(hdev, buff);
		} else {
			snprintf(buff, BUFF_SZ, "\tOverflowing data length: %d\n",
					raw_data[1]-1);
			hid_debug_event(hdev, buff);
		}
		break;
	case REPORT_EE_DATA:
		/* Data buffer in response to REPORT_EE_READ or REPORT_EE_WRITE */
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_EE_DATA", report->id, size-1);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
		hid_debug_event(hdev, buff);
		if (raw_data[3] == 0) {
			snprintf(buff, BUFF_SZ, "\tNo data\n");
			hid_debug_event(hdev, buff);
		} else if (raw_data[3] + 4 <= size) {
			snprintf(buff, BUFF_SZ, "\tData: ");
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
			hid_debug_event(hdev, buff);
		} else {
			snprintf(buff, BUFF_SZ, "\tData overflowed\n");
			hid_debug_event(hdev, buff);
		}
		break;
	case REPORT_MEMORY:
		/* Data buffer in response to REPORT_READ_MEMORY or REPORT_WRITE_MEMORY */
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		switch (data->addr_sz) {
		case 2:
			snprintf(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
					raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snprintf(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
			hid_debug_event(hdev, buff);
			if (raw_data[3] == 0) {
				snprintf(buff, BUFF_SZ, "\tNo data\n");
			} else if (raw_data[3] + 4 <= size) {
				snprintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
			} else {
				snprintf(buff, BUFF_SZ, "\tData overflowed\n");
			}
			break;
		case 3:
			snprintf(buff, BUFF_SZ, "\tData address: 0x%02x%02x%02x\n",
					raw_data[3], raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snprintf(buff, BUFF_SZ, "\tData length: %d\n", raw_data[4]);
			hid_debug_event(hdev, buff);
			if (raw_data[4] == 0) {
				snprintf(buff, BUFF_SZ, "\tNo data\n");
			} else if (raw_data[4] + 5 <= size) {
				snprintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+5, raw_data[4]);
			} else {
				snprintf(buff, BUFF_SZ, "\tData overflowed\n");
			}
			break;
		default:
			snprintf(buff, BUFF_SZ, "\tNot supported\n");
		}
		hid_debug_event(hdev, buff);
		break;
	case REPORT_VERSION:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_VERSION", report->id, size-1);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tFirmware version: %d.%d\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		break;
	case REPORT_BL_ERASE_MEMORY:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_ERASE_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		break;
	case REPORT_BL_READ_MEMORY:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_READ_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		break;
	case REPORT_BL_WRITE_MEMORY:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_WRITE_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		break;
	case REPORT_DEVID:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_DEVID", report->id, size-1);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tSerial: 0x%02x%02x%02x%02x\n",
				raw_data[1], raw_data[2], raw_data[3], raw_data[4]);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tType: 0x%02x\n",
				raw_data[5]);
		hid_debug_event(hdev, buff);
		break;
	case REPORT_SPLASH_SIZE:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_SPLASH_SIZE", report->id, size-1);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tTotal splash space: %d\n",
				(raw_data[2] << 8) | raw_data[1]);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tUsed splash space: %d\n",
				(raw_data[4] << 8) | raw_data[3]);
		hid_debug_event(hdev, buff);
		break;
	case REPORT_HOOK_VERSION:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_HOOK_VERSION", report->id, size-1);
		hid_debug_event(hdev, buff);
		snprintf(buff, BUFF_SZ, "\tFirmware version: %d.%d\n",
				raw_data[1], raw_data[2]);
		hid_debug_event(hdev, buff);
		break;
	default:
		snprintf(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"<unknown>", report->id, size-1);
		hid_debug_event(hdev, buff);
		break;
	}
	wake_up_interruptible(&hdev->debug_wait);
	kfree(buff);
}