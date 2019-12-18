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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {int needs_remote_wakeup; TYPE_2__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  phydev; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  access_lock; } ;
struct lan78xx_net {int delta; scalar_t__ hard_mtu; int /*<<< orphan*/  urb_intr; int /*<<< orphan*/  pipe_out; struct usb_device* udev; void* maxpacket; int /*<<< orphan*/  pipe_intr; TYPE_4__* ep_intr; int /*<<< orphan*/  pipe_in; TYPE_4__* ep_blkout; TYPE_4__* ep_blkin; TYPE_1__ stats; int /*<<< orphan*/  stat_monitor; int /*<<< orphan*/  deferred; int /*<<< orphan*/  wq; int /*<<< orphan*/  bh; int /*<<< orphan*/  phy_mutex; int /*<<< orphan*/  txq_pend; int /*<<< orphan*/  rxq_pause; int /*<<< orphan*/  done; int /*<<< orphan*/  txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  msg_enable; struct net_device* net; struct usb_interface* intf; } ;
struct TYPE_7__ {int bEndpointAddress; unsigned int bInterval; } ;
struct TYPE_8__ {TYPE_3__ desc; } ;
struct TYPE_6__ {TYPE_4__* endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_IN_PIPE ; 
 int /*<<< orphan*/  BULK_OUT_PIPE ; 
 int /*<<< orphan*/  DEFAULT_AUTOSUSPEND_DELAY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SINGLE_PACKET_SIZE ; 
 int NETIF_MSG_DRV ; 
 int NETIF_MSG_LINK ; 
 int NETIF_MSG_PROBE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT_JIFFIES ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  intr_complete ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_bh ; 
 int lan78xx_bind (struct lan78xx_net*,struct usb_interface*) ; 
 int /*<<< orphan*/  lan78xx_delayedwork ; 
 int /*<<< orphan*/  lan78xx_ethtool_ops ; 
 int /*<<< orphan*/  lan78xx_netdev_ops ; 
 int lan78xx_phy_init (struct lan78xx_net*) ; 
 int /*<<< orphan*/  lan78xx_stat_monitor ; 
 int /*<<< orphan*/  lan78xx_unbind (struct lan78xx_net*,struct usb_interface*) ; 
 int /*<<< orphan*/  msg_level ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct lan78xx_net*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,struct lan78xx_net*,unsigned int) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_device* usb_get_dev (struct usb_device*) ; 
 void* usb_maxpacket (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct lan78xx_net*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct lan78xx_net *dev;
	struct net_device *netdev;
	struct usb_device *udev;
	int ret;
	unsigned maxp;
	unsigned period;
	u8 *buf = NULL;

	udev = interface_to_usbdev(intf);
	udev = usb_get_dev(udev);

	netdev = alloc_etherdev(sizeof(struct lan78xx_net));
	if (!netdev) {
		dev_err(&intf->dev, "Error: OOM\n");
		ret = -ENOMEM;
		goto out1;
	}

	/* netdev_printk() needs this */
	SET_NETDEV_DEV(netdev, &intf->dev);

	dev = netdev_priv(netdev);
	dev->udev = udev;
	dev->intf = intf;
	dev->net = netdev;
	dev->msg_enable = netif_msg_init(msg_level, NETIF_MSG_DRV
					| NETIF_MSG_PROBE | NETIF_MSG_LINK);

	skb_queue_head_init(&dev->rxq);
	skb_queue_head_init(&dev->txq);
	skb_queue_head_init(&dev->done);
	skb_queue_head_init(&dev->rxq_pause);
	skb_queue_head_init(&dev->txq_pend);
	mutex_init(&dev->phy_mutex);

	tasklet_init(&dev->bh, lan78xx_bh, (unsigned long)dev);
	INIT_DELAYED_WORK(&dev->wq, lan78xx_delayedwork);
	init_usb_anchor(&dev->deferred);

	netdev->netdev_ops = &lan78xx_netdev_ops;
	netdev->watchdog_timeo = TX_TIMEOUT_JIFFIES;
	netdev->ethtool_ops = &lan78xx_ethtool_ops;

	dev->delta = 1;
	timer_setup(&dev->stat_monitor, lan78xx_stat_monitor, 0);

	mutex_init(&dev->stats.access_lock);

	ret = lan78xx_bind(dev, intf);
	if (ret < 0)
		goto out2;

	if (netdev->mtu > (dev->hard_mtu - netdev->hard_header_len))
		netdev->mtu = dev->hard_mtu - netdev->hard_header_len;

	/* MTU range: 68 - 9000 */
	netdev->max_mtu = MAX_SINGLE_PACKET_SIZE;

	dev->ep_blkin = (intf->cur_altsetting)->endpoint + 0;
	dev->ep_blkout = (intf->cur_altsetting)->endpoint + 1;
	dev->ep_intr = (intf->cur_altsetting)->endpoint + 2;

	dev->pipe_in = usb_rcvbulkpipe(udev, BULK_IN_PIPE);
	dev->pipe_out = usb_sndbulkpipe(udev, BULK_OUT_PIPE);

	dev->pipe_intr = usb_rcvintpipe(dev->udev,
					dev->ep_intr->desc.bEndpointAddress &
					USB_ENDPOINT_NUMBER_MASK);
	period = dev->ep_intr->desc.bInterval;

	maxp = usb_maxpacket(dev->udev, dev->pipe_intr, 0);
	buf = kmalloc(maxp, GFP_KERNEL);
	if (buf) {
		dev->urb_intr = usb_alloc_urb(0, GFP_KERNEL);
		if (!dev->urb_intr) {
			ret = -ENOMEM;
			kfree(buf);
			goto out3;
		} else {
			usb_fill_int_urb(dev->urb_intr, dev->udev,
					 dev->pipe_intr, buf, maxp,
					 intr_complete, dev, period);
		}
	}

	dev->maxpacket = usb_maxpacket(dev->udev, dev->pipe_out, 1);

	/* driver requires remote-wakeup capability during autosuspend. */
	intf->needs_remote_wakeup = 1;

	ret = lan78xx_phy_init(dev);
	if (ret < 0)
		goto out4;

	ret = register_netdev(netdev);
	if (ret != 0) {
		netif_err(dev, probe, netdev, "couldn't register the device\n");
		goto out5;
	}

	usb_set_intfdata(intf, dev);

	ret = device_set_wakeup_enable(&udev->dev, true);

	 /* Default delay of 2sec has more overhead than advantage.
	  * Set to 10sec as default.
	  */
	pm_runtime_set_autosuspend_delay(&udev->dev,
					 DEFAULT_AUTOSUSPEND_DELAY);

	return 0;

out5:
	phy_disconnect(netdev->phydev);
out4:
	usb_free_urb(dev->urb_intr);
out3:
	lan78xx_unbind(dev, intf);
out2:
	free_netdev(netdev);
out1:
	usb_put_dev(udev);

	return ret;
}