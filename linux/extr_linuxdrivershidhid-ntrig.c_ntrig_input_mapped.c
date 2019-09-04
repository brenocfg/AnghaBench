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
struct hid_usage {scalar_t__ type; int /*<<< orphan*/  code; } ;
struct hid_input {int dummy; } ;
struct hid_field {scalar_t__ physical; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EV_ABS ; 
 scalar_t__ EV_KEY ; 
 scalar_t__ EV_REL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int ntrig_input_mapped(struct hid_device *hdev, struct hid_input *hi,
			      struct hid_field *field, struct hid_usage *usage,
			      unsigned long **bit, int *max)
{
	/* No special mappings needed for the pen and single touch */
	if (field->physical)
		return 0;

	if (usage->type == EV_KEY || usage->type == EV_REL
			|| usage->type == EV_ABS)
		clear_bit(usage->code, *bit);

	return 0;
}