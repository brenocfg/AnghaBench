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
struct hid_device {int claimed; int /*<<< orphan*/  (* hiddev_hid_event ) (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int HID_CLAIMED_HIDDEV ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt_touch_event(struct hid_device *hid, struct hid_field *field,
				struct hid_usage *usage, __s32 value)
{
	/* we will handle the hidinput part later, now remains hiddev */
	if (hid->claimed & HID_CLAIMED_HIDDEV && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, field, usage, value);

	return 1;
}