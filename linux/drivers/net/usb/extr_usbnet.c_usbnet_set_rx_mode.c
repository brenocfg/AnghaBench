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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_SET_RX_MODE ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usbnet_defer_kevent (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbnet_set_rx_mode(struct net_device *net)
{
	struct usbnet		*dev = netdev_priv(net);

	usbnet_defer_kevent(dev, EVENT_SET_RX_MODE);
}