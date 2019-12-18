#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct urb {int dummy; } ;
struct TYPE_6__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct ucan_priv {int /*<<< orphan*/  netdev; TYPE_3__ can; TYPE_2__* ctl_msg_buffer; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {TYPE_1__ cmd_start; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CAN_CTRLMODE_ONE_SHOT ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  UCAN_COMMAND_RESET ; 
 int /*<<< orphan*/  UCAN_COMMAND_START ; 
 int /*<<< orphan*/  UCAN_COMMAND_STOP ; 
 int UCAN_MAX_RX_URBS ; 
 int /*<<< orphan*/  UCAN_MODE_3_SAMPLES ; 
 int /*<<< orphan*/  UCAN_MODE_BERR_REPORT ; 
 int /*<<< orphan*/  UCAN_MODE_LOOPBACK ; 
 int /*<<< orphan*/  UCAN_MODE_ONE_SHOT ; 
 int /*<<< orphan*/  UCAN_MODE_SILENT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct ucan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int ucan_alloc_context_array (struct ucan_priv*) ; 
 int /*<<< orphan*/  ucan_cleanup_rx_urbs (struct ucan_priv*,struct urb**) ; 
 int ucan_ctrl_command_out (struct ucan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ucan_prepare_and_anchor_rx_urbs (struct ucan_priv*,struct urb**) ; 
 int /*<<< orphan*/  ucan_release_context_array (struct ucan_priv*) ; 
 int ucan_submit_rx_urbs (struct ucan_priv*,struct urb**) ; 

__attribute__((used)) static int ucan_open(struct net_device *netdev)
{
	int ret, ret_cleanup;
	u16 ctrlmode;
	struct urb *urbs[UCAN_MAX_RX_URBS];
	struct ucan_priv *up = netdev_priv(netdev);

	ret = ucan_alloc_context_array(up);
	if (ret)
		return ret;

	/* Allocate and prepare IN URBS - allocated and anchored
	 * urbs are stored in urbs[] for clean
	 */
	ret = ucan_prepare_and_anchor_rx_urbs(up, urbs);
	if (ret)
		goto err_contexts;

	/* Check the control mode */
	ctrlmode = 0;
	if (up->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		ctrlmode |= UCAN_MODE_LOOPBACK;
	if (up->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		ctrlmode |= UCAN_MODE_SILENT;
	if (up->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		ctrlmode |= UCAN_MODE_3_SAMPLES;
	if (up->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		ctrlmode |= UCAN_MODE_ONE_SHOT;

	/* Enable this in any case - filtering is down within the
	 * receive path
	 */
	ctrlmode |= UCAN_MODE_BERR_REPORT;
	up->ctl_msg_buffer->cmd_start.mode = cpu_to_le16(ctrlmode);

	/* Driver is ready to receive data - start the USB device */
	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_START, 0, 2);
	if (ret < 0) {
		netdev_err(up->netdev,
			   "could not start device, code: %d\n",
			   ret);
		goto err_reset;
	}

	/* Call CAN layer open */
	ret = open_candev(netdev);
	if (ret)
		goto err_stop;

	/* Driver is ready to receive data. Submit RX URBS */
	ret = ucan_submit_rx_urbs(up, urbs);
	if (ret)
		goto err_stop;

	up->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Start the network queue */
	netif_start_queue(netdev);

	return 0;

err_stop:
	/* The device have started already stop it */
	ret_cleanup = ucan_ctrl_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	if (ret_cleanup < 0)
		netdev_err(up->netdev,
			   "could not stop device, code: %d\n",
			   ret_cleanup);

err_reset:
	/* The device might have received data, reset it for
	 * consistent state
	 */
	ret_cleanup = ucan_ctrl_command_out(up, UCAN_COMMAND_RESET, 0, 0);
	if (ret_cleanup < 0)
		netdev_err(up->netdev,
			   "could not reset device, code: %d\n",
			   ret_cleanup);

	/* clean up unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);

err_contexts:
	ucan_release_context_array(up);
	return ret;
}