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
struct hid_device_id {scalar_t__ bus; scalar_t__ group; scalar_t__ vendor; scalar_t__ product; } ;
struct hid_device {scalar_t__ bus; scalar_t__ group; scalar_t__ vendor; scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ HID_ANY_ID ; 
 scalar_t__ HID_BUS_ANY ; 
 scalar_t__ HID_GROUP_ANY ; 

bool hid_match_one_id(const struct hid_device *hdev,
		      const struct hid_device_id *id)
{
	return (id->bus == HID_BUS_ANY || id->bus == hdev->bus) &&
		(id->group == HID_GROUP_ANY || id->group == hdev->group) &&
		(id->vendor == HID_ANY_ID || id->vendor == hdev->vendor) &&
		(id->product == HID_ANY_ID || id->product == hdev->product);
}