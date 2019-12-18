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
typedef  int /*<<< orphan*/  u8 ;
struct wacom_features {int quirks; } ;
struct wacom_wac {unsigned int* serial; unsigned int* id; int /*<<< orphan*/  pen_fifo; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_report {int maxfield; struct hid_field** field; } ;
struct hid_field {int maxusage; unsigned int report_offset; unsigned int report_size; struct hid_usage* usage; } ;
struct hid_device {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 unsigned int HID_DG_INRANGE ; 
#define  HID_DG_TOOLSERIALNUMBER 130 
#define  WACOM_HID_WD_SERIALHI 129 
#define  WACOM_HID_WD_TOOLTYPE 128 
 int WACOM_QUIRK_TOOLSERIAL ; 
 unsigned int hid_field_extract (struct hid_device*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_wac_queue_flush (struct hid_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wacom_wac_queue_insert (struct hid_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wacom_wac_pen_serial_enforce(struct hid_device *hdev,
		struct hid_report *report, u8 *raw_data, int report_size)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;
	bool flush = false;
	bool insert = false;
	int i, j;

	if (wacom_wac->serial[0] || !(features->quirks & WACOM_QUIRK_TOOLSERIAL))
		return 0;

	/* Queue events which have invalid tool type or serial number */
	for (i = 0; i < report->maxfield; i++) {
		for (j = 0; j < report->field[i]->maxusage; j++) {
			struct hid_field *field = report->field[i];
			struct hid_usage *usage = &field->usage[j];
			unsigned int equivalent_usage = wacom_equivalent_usage(usage->hid);
			unsigned int offset;
			unsigned int size;
			unsigned int value;

			if (equivalent_usage != HID_DG_INRANGE &&
			    equivalent_usage != HID_DG_TOOLSERIALNUMBER &&
			    equivalent_usage != WACOM_HID_WD_SERIALHI &&
			    equivalent_usage != WACOM_HID_WD_TOOLTYPE)
				continue;

			offset = field->report_offset;
			size = field->report_size;
			value = hid_field_extract(hdev, raw_data+1, offset + j * size, size);

			/* If we go out of range, we need to flush the queue ASAP */
			if (equivalent_usage == HID_DG_INRANGE)
				value = !value;

			if (value) {
				flush = true;
				switch (equivalent_usage) {
				case HID_DG_TOOLSERIALNUMBER:
					wacom_wac->serial[0] = value;
					break;

				case WACOM_HID_WD_SERIALHI:
					wacom_wac->serial[0] |= ((__u64)value) << 32;
					break;

				case WACOM_HID_WD_TOOLTYPE:
					wacom_wac->id[0] = value;
					break;
				}
			}
			else {
				insert = true;
			}
		}
	}

	if (flush)
		wacom_wac_queue_flush(hdev, &wacom_wac->pen_fifo);
	else if (insert)
		wacom_wac_queue_insert(hdev, &wacom_wac->pen_fifo,
				       raw_data, report_size);

	return insert && !flush;
}