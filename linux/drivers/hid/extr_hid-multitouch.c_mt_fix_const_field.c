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
struct hid_field {int flags; TYPE_1__* usage; } ;
struct TYPE_2__ {unsigned int hid; } ;

/* Variables and functions */
 int HID_MAIN_ITEM_CONSTANT ; 
 int HID_MAIN_ITEM_VARIABLE ; 

__attribute__((used)) static void mt_fix_const_field(struct hid_field *field, unsigned int usage)
{
	if (field->usage[0].hid != usage ||
	    !(field->flags & HID_MAIN_ITEM_CONSTANT))
		return;

	field->flags &= ~HID_MAIN_ITEM_CONSTANT;
	field->flags |= HID_MAIN_ITEM_VARIABLE;
}