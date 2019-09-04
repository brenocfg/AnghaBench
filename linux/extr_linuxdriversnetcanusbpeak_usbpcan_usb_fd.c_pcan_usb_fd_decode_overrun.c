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
struct sk_buff {int dummy; } ;
struct pucan_msg {int dummy; } ;
struct peak_usb_device {struct net_device* netdev; } ;
struct pcan_usb_fd_if {int /*<<< orphan*/  time_ref; struct peak_usb_device** dev; } ;
struct pcan_ufd_ovr_msg {int /*<<< orphan*/  ts_low; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct can_frame {int /*<<< orphan*/ * data; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_OVERFLOW ; 
 int ENOMEM ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_netif_rx (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t pufd_omsg_get_channel (struct pcan_ufd_ovr_msg*) ; 

__attribute__((used)) static int pcan_usb_fd_decode_overrun(struct pcan_usb_fd_if *usb_if,
				      struct pucan_msg *rx_msg)
{
	struct pcan_ufd_ovr_msg *ov = (struct pcan_ufd_ovr_msg *)rx_msg;
	struct peak_usb_device *dev = usb_if->dev[pufd_omsg_get_channel(ov)];
	struct net_device *netdev = dev->netdev;
	struct can_frame *cf;
	struct sk_buff *skb;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(netdev, &cf);
	if (!skb)
		return -ENOMEM;

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;

	peak_usb_netif_rx(skb, &usb_if->time_ref, le32_to_cpu(ov->ts_low));

	netdev->stats.rx_over_errors++;
	netdev->stats.rx_errors++;

	return 0;
}