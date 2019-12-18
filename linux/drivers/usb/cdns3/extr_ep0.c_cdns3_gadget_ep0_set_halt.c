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
struct usb_ep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cdns3_gadget_ep0_set_halt(struct usb_ep *ep, int value)
{
	/* TODO */
	return 0;
}