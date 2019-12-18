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
struct usb_string {int id; scalar_t__ s; } ;
struct usb_composite_dev {int next_string_id; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ unlikely (int) ; 

int usb_string_ids_tab(struct usb_composite_dev *cdev, struct usb_string *str)
{
	int next = cdev->next_string_id;

	for (; str->s; ++str) {
		if (unlikely(next >= 254))
			return -ENODEV;
		str->id = ++next;
	}

	cdev->next_string_id = next;

	return 0;
}