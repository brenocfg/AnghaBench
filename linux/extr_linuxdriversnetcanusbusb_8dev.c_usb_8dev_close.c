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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct usb_8dev_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 struct usb_8dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  unlink_all_urbs (struct usb_8dev_priv*) ; 
 int usb_8dev_cmd_close (struct usb_8dev_priv*) ; 

__attribute__((used)) static int usb_8dev_close(struct net_device *netdev)
{
	struct usb_8dev_priv *priv = netdev_priv(netdev);
	int err = 0;

	/* Send CLOSE command to CAN controller */
	err = usb_8dev_cmd_close(priv);
	if (err)
		netdev_warn(netdev, "couldn't stop device");

	priv->can.state = CAN_STATE_STOPPED;

	netif_stop_queue(netdev);

	/* Stop polling */
	unlink_all_urbs(priv);

	close_candev(netdev);

	can_led_event(netdev, CAN_LED_EVENT_STOP);

	return err;
}