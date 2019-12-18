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
typedef  int u8 ;
struct usb_os_desc {scalar_t__ ext_compat_id; } ;
struct usb_function {int os_desc_n; TYPE_1__* os_desc_table; } ;
struct usb_configuration {int next_interface_id; struct usb_function** interface; } ;
struct TYPE_2__ {int if_id; struct usb_os_desc* os_desc; } ;

/* Variables and functions */
 int USB_COMP_EP0_OS_DESC_BUFSIZ ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__,int) ; 

__attribute__((used)) static int fill_ext_compat(struct usb_configuration *c, u8 *buf)
{
	int i, count;

	count = 16;
	buf += 16;
	for (i = 0; i < c->next_interface_id; ++i) {
		struct usb_function *f;
		int j;

		f = c->interface[i];
		for (j = 0; j < f->os_desc_n; ++j) {
			struct usb_os_desc *d;

			if (i != f->os_desc_table[j].if_id)
				continue;
			d = f->os_desc_table[j].os_desc;
			if (d && d->ext_compat_id) {
				*buf++ = i;
				*buf++ = 0x01;
				memcpy(buf, d->ext_compat_id, 16);
				buf += 22;
			} else {
				++buf;
				*buf = 0x01;
				buf += 23;
			}
			count += 24;
			if (count + 24 >= USB_COMP_EP0_OS_DESC_BUFSIZ)
				return count;
		}
	}

	return count;
}