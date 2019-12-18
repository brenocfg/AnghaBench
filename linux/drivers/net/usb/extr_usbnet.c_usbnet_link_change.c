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
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_LINK_CHANGE ; 
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbnet_defer_kevent (struct usbnet*,int /*<<< orphan*/ ) ; 

void usbnet_link_change(struct usbnet *dev, bool link, bool need_reset)
{
	/* update link after link is reseted */
	if (link && !need_reset)
		netif_carrier_on(dev->net);
	else
		netif_carrier_off(dev->net);

	if (need_reset && link)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	else
		usbnet_defer_kevent(dev, EVENT_LINK_CHANGE);
}