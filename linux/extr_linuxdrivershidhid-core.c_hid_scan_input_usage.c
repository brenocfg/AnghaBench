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
typedef  scalar_t__ u32 ;
struct hid_parser {struct hid_device* device; } ;
struct hid_device {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 scalar_t__ HID_DG_CONTACTID ; 
 int /*<<< orphan*/  HID_GROUP_MULTITOUCH ; 

__attribute__((used)) static void hid_scan_input_usage(struct hid_parser *parser, u32 usage)
{
	struct hid_device *hid = parser->device;

	if (usage == HID_DG_CONTACTID)
		hid->group = HID_GROUP_MULTITOUCH;
}