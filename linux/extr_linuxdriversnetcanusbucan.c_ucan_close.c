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
struct ucan_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  rx_urbs; int /*<<< orphan*/  tx_urbs; TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  UCAN_COMMAND_RESET ; 
 int /*<<< orphan*/  UCAN_COMMAND_STOP ; 
 int /*<<< orphan*/  close_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct ucan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int ucan_ctrl_command_out (struct ucan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucan_release_context_array (struct ucan_priv*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ucan_close(struct net_device *netdev)
{
	int ret;
	struct ucan_priv *up = netdev_priv(netdev);

	up->can.state = CAN_STATE_STOPPED;

	/* stop sending data */
	usb_kill_anchored_urbs(&up->tx_urbs);

	/* stop receiving data */
	usb_kill_anchored_urbs(&up->rx_urbs);

	/* stop and reset can device */
	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	if (ret < 0)
		netdev_err(up->netdev,
			   "could not stop device, code: %d\n",
			   ret);

	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_RESET, 0, 0);
	if (ret < 0)
		netdev_err(up->netdev,
			   "could not reset device, code: %d\n",
			   ret);

	netif_stop_queue(netdev);

	ucan_release_context_array(up);

	close_candev(up->netdev);
	return 0;
}