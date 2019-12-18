#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct gs_device_config {int sw_version; } ;
struct gs_device_bt_const {int feature; int /*<<< orphan*/  fclk_can; int /*<<< orphan*/  brp_inc; int /*<<< orphan*/  brp_max; int /*<<< orphan*/  brp_min; int /*<<< orphan*/  sjw_max; int /*<<< orphan*/  tseg2_max; int /*<<< orphan*/  tseg2_min; int /*<<< orphan*/  tseg1_max; int /*<<< orphan*/  tseg1_min; } ;
struct TYPE_6__ {int /*<<< orphan*/  freq; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctrlmode_supported; int /*<<< orphan*/  do_set_bittiming; TYPE_3__* bittiming_const; TYPE_2__ clock; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  brp_inc; int /*<<< orphan*/  brp_max; int /*<<< orphan*/  brp_min; int /*<<< orphan*/  sjw_max; int /*<<< orphan*/  tseg2_max; int /*<<< orphan*/  tseg2_min; int /*<<< orphan*/  tseg1_max; int /*<<< orphan*/  tseg1_min; int /*<<< orphan*/  name; } ;
struct gs_can {unsigned int channel; struct net_device* netdev; TYPE_4__ can; TYPE_3__ bt_const; TYPE_1__* tx_context; int /*<<< orphan*/  tx_ctx_lock; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; struct usb_interface* iface; int /*<<< orphan*/  udev; } ;
struct TYPE_5__ {int echo_id; struct gs_can* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  CAN_CTRLMODE_ONE_SHOT ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int ENOMEM ; 
 struct gs_can* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GS_CAN_FEATURE_IDENTIFY ; 
 int GS_CAN_FEATURE_LISTEN_ONLY ; 
 int GS_CAN_FEATURE_LOOP_BACK ; 
 int GS_CAN_FEATURE_ONE_SHOT ; 
 int GS_CAN_FEATURE_TRIPLE_SAMPLE ; 
 int GS_MAX_TX_URBS ; 
 int /*<<< orphan*/  GS_USB_BREQ_BT_CONST ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 struct net_device* alloc_candev (int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  gs_usb_ethtool_ops ; 
 int /*<<< orphan*/  gs_usb_netdev_ops ; 
 int /*<<< orphan*/  gs_usb_set_bittiming ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gs_device_bt_const*) ; 
 struct gs_device_bt_const* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct gs_can* netdev_priv (struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,struct gs_device_bt_const*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gs_can *gs_make_candev(unsigned int channel,
				     struct usb_interface *intf,
				     struct gs_device_config *dconf)
{
	struct gs_can *dev;
	struct net_device *netdev;
	int rc;
	struct gs_device_bt_const *bt_const;

	bt_const = kmalloc(sizeof(*bt_const), GFP_KERNEL);
	if (!bt_const)
		return ERR_PTR(-ENOMEM);

	/* fetch bit timing constants */
	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_rcvctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_BT_CONST,
			     USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     channel,
			     0,
			     bt_const,
			     sizeof(*bt_const),
			     1000);

	if (rc < 0) {
		dev_err(&intf->dev,
			"Couldn't get bit timing const for channel (err=%d)\n",
			rc);
		kfree(bt_const);
		return ERR_PTR(rc);
	}

	/* create netdev */
	netdev = alloc_candev(sizeof(struct gs_can), GS_MAX_TX_URBS);
	if (!netdev) {
		dev_err(&intf->dev, "Couldn't allocate candev\n");
		kfree(bt_const);
		return ERR_PTR(-ENOMEM);
	}

	dev = netdev_priv(netdev);

	netdev->netdev_ops = &gs_usb_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support full roundtrip echo */

	/* dev settup */
	strcpy(dev->bt_const.name, "gs_usb");
	dev->bt_const.tseg1_min = bt_const->tseg1_min;
	dev->bt_const.tseg1_max = bt_const->tseg1_max;
	dev->bt_const.tseg2_min = bt_const->tseg2_min;
	dev->bt_const.tseg2_max = bt_const->tseg2_max;
	dev->bt_const.sjw_max = bt_const->sjw_max;
	dev->bt_const.brp_min = bt_const->brp_min;
	dev->bt_const.brp_max = bt_const->brp_max;
	dev->bt_const.brp_inc = bt_const->brp_inc;

	dev->udev = interface_to_usbdev(intf);
	dev->iface = intf;
	dev->netdev = netdev;
	dev->channel = channel;

	init_usb_anchor(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);
	spin_lock_init(&dev->tx_ctx_lock);
	for (rc = 0; rc < GS_MAX_TX_URBS; rc++) {
		dev->tx_context[rc].dev = dev;
		dev->tx_context[rc].echo_id = GS_MAX_TX_URBS;
	}

	/* can settup */
	dev->can.state = CAN_STATE_STOPPED;
	dev->can.clock.freq = bt_const->fclk_can;
	dev->can.bittiming_const = &dev->bt_const;
	dev->can.do_set_bittiming = gs_usb_set_bittiming;

	dev->can.ctrlmode_supported = 0;

	if (bt_const->feature & GS_CAN_FEATURE_LISTEN_ONLY)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_LISTENONLY;

	if (bt_const->feature & GS_CAN_FEATURE_LOOP_BACK)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_LOOPBACK;

	if (bt_const->feature & GS_CAN_FEATURE_TRIPLE_SAMPLE)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;

	if (bt_const->feature & GS_CAN_FEATURE_ONE_SHOT)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_ONE_SHOT;

	SET_NETDEV_DEV(netdev, &intf->dev);

	if (dconf->sw_version > 1)
		if (bt_const->feature & GS_CAN_FEATURE_IDENTIFY)
			netdev->ethtool_ops = &gs_usb_ethtool_ops;

	kfree(bt_const);

	rc = register_candev(dev->netdev);
	if (rc) {
		free_candev(dev->netdev);
		dev_err(&intf->dev, "Couldn't register candev (err=%d)\n", rc);
		return ERR_PTR(rc);
	}

	return dev;
}