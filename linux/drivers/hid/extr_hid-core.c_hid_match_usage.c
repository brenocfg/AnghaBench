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
struct hid_usage_id {int usage_type; int usage_hid; int usage_code; } ;
struct hid_usage {int hid; int type; int code; } ;
struct hid_device {TYPE_1__* driver; } ;
struct TYPE_2__ {struct hid_usage_id* usage_table; } ;

/* Variables and functions */
 int HID_ANY_ID ; 

__attribute__((used)) static int hid_match_usage(struct hid_device *hid, struct hid_usage *usage)
{
	const struct hid_usage_id *id = hid->driver->usage_table;

	if (!id) /* NULL means all */
		return 1;

	for (; id->usage_type != HID_ANY_ID - 1; id++)
		if ((id->usage_hid == HID_ANY_ID ||
				id->usage_hid == usage->hid) &&
				(id->usage_type == HID_ANY_ID ||
				id->usage_type == usage->type) &&
				(id->usage_code == HID_ANY_ID ||
				 id->usage_code == usage->code))
			return 1;
	return 0;
}