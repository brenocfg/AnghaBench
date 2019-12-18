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
struct usb_os_desc {scalar_t__ ext_prop_len; } ;
struct usb_function {int os_desc_n; TYPE_1__* os_desc_table; } ;
struct usb_configuration {struct usb_function** interface; } ;
struct TYPE_2__ {int if_id; struct usb_os_desc* os_desc; } ;

/* Variables and functions */
 int min (scalar_t__,int) ; 

__attribute__((used)) static int len_ext_prop(struct usb_configuration *c, int interface)
{
	struct usb_function *f;
	struct usb_os_desc *d;
	int j, res;

	res = 10; /* header length */
	f = c->interface[interface];
	for (j = 0; j < f->os_desc_n; ++j) {
		if (interface != f->os_desc_table[j].if_id)
			continue;
		d = f->os_desc_table[j].os_desc;
		if (d)
			return min(res + d->ext_prop_len, 4096);
	}
	return res;
}