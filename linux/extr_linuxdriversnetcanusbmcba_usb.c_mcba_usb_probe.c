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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  do_set_bittiming; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/  do_set_termination; void* bitrate_const_cnt; void* bitrate_const; void* termination_const_cnt; void* termination_const; int /*<<< orphan*/  state; } ;
struct mcba_priv {int usb_ka_first_pass; int can_ka_first_pass; int can_speed_check; struct net_device* netdev; TYPE_1__ can; int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  rx_submitted; struct usb_device* udev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  MCBA_MAX_TX_URBS ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 void* mcba_bitrate ; 
 int /*<<< orphan*/  mcba_net_get_berr_counter ; 
 int /*<<< orphan*/  mcba_net_set_bittiming ; 
 int /*<<< orphan*/  mcba_net_set_mode ; 
 int /*<<< orphan*/  mcba_netdev_ops ; 
 int /*<<< orphan*/  mcba_set_termination ; 
 void* mcba_termination ; 
 int mcba_usb_start (struct mcba_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct mcba_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct mcba_priv*) ; 

__attribute__((used)) static int mcba_usb_probe(struct usb_interface *intf,
			  const struct usb_device_id *id)
{
	struct net_device *netdev;
	struct mcba_priv *priv;
	int err = -ENOMEM;
	struct usb_device *usbdev = interface_to_usbdev(intf);

	netdev = alloc_candev(sizeof(struct mcba_priv), MCBA_MAX_TX_URBS);
	if (!netdev) {
		dev_err(&intf->dev, "Couldn't alloc candev\n");
		return -ENOMEM;
	}

	priv = netdev_priv(netdev);

	priv->udev = usbdev;
	priv->netdev = netdev;
	priv->usb_ka_first_pass = true;
	priv->can_ka_first_pass = true;
	priv->can_speed_check = false;

	init_usb_anchor(&priv->rx_submitted);
	init_usb_anchor(&priv->tx_submitted);

	usb_set_intfdata(intf, priv);

	/* Init CAN device */
	priv->can.state = CAN_STATE_STOPPED;
	priv->can.termination_const = mcba_termination;
	priv->can.termination_const_cnt = ARRAY_SIZE(mcba_termination);
	priv->can.bitrate_const = mcba_bitrate;
	priv->can.bitrate_const_cnt = ARRAY_SIZE(mcba_bitrate);

	priv->can.do_set_termination = mcba_set_termination;
	priv->can.do_set_mode = mcba_net_set_mode;
	priv->can.do_get_berr_counter = mcba_net_get_berr_counter;
	priv->can.do_set_bittiming = mcba_net_set_bittiming;

	netdev->netdev_ops = &mcba_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	SET_NETDEV_DEV(netdev, &intf->dev);

	err = register_candev(netdev);
	if (err) {
		netdev_err(netdev, "couldn't register CAN device: %d\n", err);

		goto cleanup_free_candev;
	}

	devm_can_led_init(netdev);

	/* Start USB dev only if we have successfully registered CAN device */
	err = mcba_usb_start(priv);
	if (err) {
		if (err == -ENODEV)
			netif_device_detach(priv->netdev);

		netdev_warn(netdev, "couldn't start device: %d\n", err);

		goto cleanup_unregister_candev;
	}

	dev_info(&intf->dev, "Microchip CAN BUS Analyzer connected\n");

	return 0;

cleanup_unregister_candev:
	unregister_candev(priv->netdev);

cleanup_free_candev:
	free_candev(netdev);

	return err;
}