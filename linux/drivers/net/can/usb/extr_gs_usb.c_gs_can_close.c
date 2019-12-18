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
struct gs_usb {int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  active_channels; } ;
struct gs_can {TYPE_1__* tx_context; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; struct gs_usb* parent; } ;
struct TYPE_2__ {int echo_id; struct gs_can* dev; } ;

/* Variables and functions */
 int GS_MAX_TX_URBS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int gs_cmd_reset (struct gs_can*) ; 
 struct gs_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gs_can_close(struct net_device *netdev)
{
	int rc;
	struct gs_can *dev = netdev_priv(netdev);
	struct gs_usb *parent = dev->parent;

	netif_stop_queue(netdev);

	/* Stop polling */
	if (atomic_dec_and_test(&parent->active_channels))
		usb_kill_anchored_urbs(&parent->rx_submitted);

	/* Stop sending URBs */
	usb_kill_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	/* reset the device */
	rc = gs_cmd_reset(dev);
	if (rc < 0)
		netdev_warn(netdev, "Couldn't shutdown device (err=%d)", rc);

	/* reset tx contexts */
	for (rc = 0; rc < GS_MAX_TX_URBS; rc++) {
		dev->tx_context[rc].dev = dev;
		dev->tx_context[rc].echo_id = GS_MAX_TX_URBS;
	}

	/* close the netdev */
	close_candev(netdev);

	return 0;
}