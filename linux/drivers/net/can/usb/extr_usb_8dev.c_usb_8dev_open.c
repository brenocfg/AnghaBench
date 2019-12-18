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
struct usb_8dev_priv {int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int ENODEV ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 struct usb_8dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int usb_8dev_start (struct usb_8dev_priv*) ; 

__attribute__((used)) static int usb_8dev_open(struct net_device *netdev)
{
	struct usb_8dev_priv *priv = netdev_priv(netdev);
	int err;

	/* common open */
	err = open_candev(netdev);
	if (err)
		return err;

	can_led_event(netdev, CAN_LED_EVENT_OPEN);

	/* finally start device */
	err = usb_8dev_start(priv);
	if (err) {
		if (err == -ENODEV)
			netif_device_detach(priv->netdev);

		netdev_warn(netdev, "couldn't start device: %d\n",
			 err);

		close_candev(netdev);

		return err;
	}

	netif_start_queue(netdev);

	return 0;
}