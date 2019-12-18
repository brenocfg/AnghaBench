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
struct hid_usage {int hid; int /*<<< orphan*/  usage_index; int /*<<< orphan*/  collection_index; } ;
struct hid_input {int dummy; } ;
struct hid_field {int /*<<< orphan*/  application; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HID_UP_VENDOR_DEFINED_MAX ; 
 int HID_UP_VENDOR_DEFINED_MIN ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  dbg_hid (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int jabra_input_mapping(struct hid_device *hdev,
			       struct hid_input *hi,
			       struct hid_field *field,
			       struct hid_usage *usage,
			       unsigned long **bit, int *max)
{
	int is_vendor_defined =
		((usage->hid & HID_USAGE_PAGE) >= HID_UP_VENDOR_DEFINED_MIN &&
		 (usage->hid & HID_USAGE_PAGE) <= HID_UP_VENDOR_DEFINED_MAX);

	dbg_hid("hid=0x%08x appl=0x%08x coll_idx=0x%02x usage_idx=0x%02x: %s\n",
		usage->hid,
		field->application,
		usage->collection_index,
		usage->usage_index,
		is_vendor_defined ? "ignored" : "defaulted");

	/* Ignore vendor defined usages, default map standard usages */
	return is_vendor_defined ? -1 : 0;
}