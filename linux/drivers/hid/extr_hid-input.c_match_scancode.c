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
struct hid_usage {unsigned int hid; } ;

/* Variables and functions */
 unsigned int HID_USAGE ; 
 unsigned int HID_USAGE_PAGE ; 

__attribute__((used)) static bool match_scancode(struct hid_usage *usage,
			   unsigned int cur_idx, unsigned int scancode)
{
	return (usage->hid & (HID_USAGE_PAGE | HID_USAGE)) == scancode;
}