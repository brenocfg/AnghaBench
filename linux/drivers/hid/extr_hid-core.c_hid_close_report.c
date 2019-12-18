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
struct hid_report_enum {int /*<<< orphan*/  report_list; struct hid_report** report_id_hash; } ;
struct hid_report {int dummy; } ;
struct hid_device {int /*<<< orphan*/  status; scalar_t__ maxapplication; scalar_t__ maxcollection; scalar_t__ collection_size; int /*<<< orphan*/ * collection; scalar_t__ rsize; int /*<<< orphan*/ * rdesc; struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 unsigned int HID_MAX_IDS ; 
 unsigned int HID_REPORT_TYPES ; 
 int /*<<< orphan*/  HID_STAT_PARSED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_free_report (struct hid_report*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hid_report_enum*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hid_close_report(struct hid_device *device)
{
	unsigned i, j;

	for (i = 0; i < HID_REPORT_TYPES; i++) {
		struct hid_report_enum *report_enum = device->report_enum + i;

		for (j = 0; j < HID_MAX_IDS; j++) {
			struct hid_report *report = report_enum->report_id_hash[j];
			if (report)
				hid_free_report(report);
		}
		memset(report_enum, 0, sizeof(*report_enum));
		INIT_LIST_HEAD(&report_enum->report_list);
	}

	kfree(device->rdesc);
	device->rdesc = NULL;
	device->rsize = 0;

	kfree(device->collection);
	device->collection = NULL;
	device->collection_size = 0;
	device->maxcollection = 0;
	device->maxapplication = 0;

	device->status &= ~HID_STAT_PARSED;
}