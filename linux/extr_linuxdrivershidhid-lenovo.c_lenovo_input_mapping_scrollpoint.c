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
struct hid_usage {scalar_t__ hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REL ; 
 scalar_t__ HID_GD_Z ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_input_mapping_scrollpoint(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	if (usage->hid == HID_GD_Z) {
		hid_map_usage(hi, usage, bit, max, EV_REL, REL_HWHEEL);
		return 1;
	}
	return 0;
}