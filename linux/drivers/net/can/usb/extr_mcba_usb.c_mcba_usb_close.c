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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mcba_priv {TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  mcba_urb_unlink (struct mcba_priv*) ; 
 struct mcba_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int mcba_usb_close(struct net_device *netdev)
{
	struct mcba_priv *priv = netdev_priv(netdev);

	priv->can.state = CAN_STATE_STOPPED;

	netif_stop_queue(netdev);

	/* Stop polling */
	mcba_urb_unlink(priv);

	close_candev(netdev);
	can_led_event(netdev, CAN_LED_EVENT_STOP);

	return 0;
}