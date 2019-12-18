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
struct renesas_usb3_ep {scalar_t__ num; scalar_t__ started; } ;

/* Variables and functions */
 int EAGAIN ; 
 int usb3_set_halt_p0 (struct renesas_usb3_ep*,int) ; 
 int usb3_set_halt_pn (struct renesas_usb3_ep*,int,int) ; 

__attribute__((used)) static int usb3_set_halt(struct renesas_usb3_ep *usb3_ep, bool halt,
			 bool is_clear_feature)
{
	int ret = 0;

	if (halt && usb3_ep->started)
		return -EAGAIN;

	if (usb3_ep->num)
		ret = usb3_set_halt_pn(usb3_ep, halt, is_clear_feature);
	else
		ret = usb3_set_halt_p0(usb3_ep, halt);

	return ret;
}