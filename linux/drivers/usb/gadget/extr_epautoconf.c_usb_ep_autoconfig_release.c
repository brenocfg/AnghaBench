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
struct usb_ep {int claimed; int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */

void usb_ep_autoconfig_release(struct usb_ep *ep)
{
	ep->claimed = false;
	ep->driver_data = NULL;
}