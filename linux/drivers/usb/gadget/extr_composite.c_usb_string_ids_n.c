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
struct usb_composite_dev {unsigned int next_string_id; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ unlikely (int) ; 

int usb_string_ids_n(struct usb_composite_dev *c, unsigned n)
{
	unsigned next = c->next_string_id;
	if (unlikely(n > 254 || (unsigned)next + n > 254))
		return -ENODEV;
	c->next_string_id += n;
	return next + 1;
}