#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  udev; struct sk_buff* tx_skb; } ;
typedef  TYPE_2__ rtl8150_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bulk_callback ; 

__attribute__((used)) static netdev_tx_t rtl8150_start_xmit(struct sk_buff *skb,
					    struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	int count, res;

	netif_stop_queue(netdev);
	count = (skb->len < 60) ? 60 : skb->len;
	count = (count & 0x3f) ? count : count + 1;
	dev->tx_skb = skb;
	usb_fill_bulk_urb(dev->tx_urb, dev->udev, usb_sndbulkpipe(dev->udev, 2),
		      skb->data, count, write_bulk_callback, dev);
	if ((res = usb_submit_urb(dev->tx_urb, GFP_ATOMIC))) {
		/* Can we get/handle EPIPE here? */
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		else {
			dev_warn(&netdev->dev, "failed tx_urb %d\n", res);
			netdev->stats.tx_errors++;
			netif_start_queue(netdev);
		}
	} else {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->len;
		netif_trans_update(netdev);
	}

	return NETDEV_TX_OK;
}