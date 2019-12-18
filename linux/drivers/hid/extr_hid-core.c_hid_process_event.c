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
struct hid_usage {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_driver {int (* event ) (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;
struct hid_device {int claimed; int /*<<< orphan*/  (* hiddev_hid_event ) (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  debug_list; struct hid_driver* driver; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int HID_CLAIMED_HIDDEV ; 
 int HID_CLAIMED_INPUT ; 
 int /*<<< orphan*/  hid_dump_input (struct hid_device*,struct hid_usage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hid_match_usage (struct hid_device*,struct hid_usage*) ; 
 int /*<<< orphan*/  hidinput_hid_event (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hid_process_event(struct hid_device *hid, struct hid_field *field,
		struct hid_usage *usage, __s32 value, int interrupt)
{
	struct hid_driver *hdrv = hid->driver;
	int ret;

	if (!list_empty(&hid->debug_list))
		hid_dump_input(hid, usage, value);

	if (hdrv && hdrv->event && hid_match_usage(hid, usage)) {
		ret = hdrv->event(hid, field, usage, value);
		if (ret != 0) {
			if (ret < 0)
				hid_err(hid, "%s's event failed with %d\n",
						hdrv->name, ret);
			return;
		}
	}

	if (hid->claimed & HID_CLAIMED_INPUT)
		hidinput_hid_event(hid, field, usage, value);
	if (hid->claimed & HID_CLAIMED_HIDDEV && interrupt && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, field, usage, value);
}