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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct pucan_rx_msg {int /*<<< orphan*/  ts_low; int /*<<< orphan*/  d; int /*<<< orphan*/  can_id; int /*<<< orphan*/  flags; } ;
struct pucan_msg {int dummy; } ;
struct peak_usb_device {struct net_device* netdev; } ;
struct pcan_usb_fd_if {int /*<<< orphan*/  time_ref; struct peak_usb_device** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct canfd_frame {scalar_t__ len; int /*<<< orphan*/  data; int /*<<< orphan*/  can_id; int /*<<< orphan*/  flags; } ;
struct can_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_BRS ; 
 int /*<<< orphan*/  CANFD_ESI ; 
 int /*<<< orphan*/  CAN_EFF_FLAG ; 
 int /*<<< orphan*/  CAN_RTR_FLAG ; 
 int ENOMEM ; 
 int const PUCAN_MSG_BITRATE_SWITCH ; 
 int const PUCAN_MSG_ERROR_STATE_IND ; 
 int const PUCAN_MSG_EXT_DATA_LEN ; 
 int const PUCAN_MSG_EXT_ID ; 
 int const PUCAN_MSG_RTR ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 struct sk_buff* alloc_canfd_skb (struct net_device*,struct canfd_frame**) ; 
 scalar_t__ can_dlc2len (int /*<<< orphan*/ ) ; 
 scalar_t__ get_can_dlc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_canfd_dlc (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  peak_usb_netif_rx (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t pucan_msg_get_channel (struct pucan_rx_msg*) ; 
 int /*<<< orphan*/  pucan_msg_get_dlc (struct pucan_rx_msg*) ; 

__attribute__((used)) static int pcan_usb_fd_decode_canmsg(struct pcan_usb_fd_if *usb_if,
				     struct pucan_msg *rx_msg)
{
	struct pucan_rx_msg *rm = (struct pucan_rx_msg *)rx_msg;
	struct peak_usb_device *dev = usb_if->dev[pucan_msg_get_channel(rm)];
	struct net_device *netdev = dev->netdev;
	struct canfd_frame *cfd;
	struct sk_buff *skb;
	const u16 rx_msg_flags = le16_to_cpu(rm->flags);

	if (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN) {
		/* CANFD frame case */
		skb = alloc_canfd_skb(netdev, &cfd);
		if (!skb)
			return -ENOMEM;

		if (rx_msg_flags & PUCAN_MSG_BITRATE_SWITCH)
			cfd->flags |= CANFD_BRS;

		if (rx_msg_flags & PUCAN_MSG_ERROR_STATE_IND)
			cfd->flags |= CANFD_ESI;

		cfd->len = can_dlc2len(get_canfd_dlc(pucan_msg_get_dlc(rm)));
	} else {
		/* CAN 2.0 frame case */
		skb = alloc_can_skb(netdev, (struct can_frame **)&cfd);
		if (!skb)
			return -ENOMEM;

		cfd->len = get_can_dlc(pucan_msg_get_dlc(rm));
	}

	cfd->can_id = le32_to_cpu(rm->can_id);

	if (rx_msg_flags & PUCAN_MSG_EXT_ID)
		cfd->can_id |= CAN_EFF_FLAG;

	if (rx_msg_flags & PUCAN_MSG_RTR)
		cfd->can_id |= CAN_RTR_FLAG;
	else
		memcpy(cfd->data, rm->d, cfd->len);

	peak_usb_netif_rx(skb, &usb_if->time_ref, le32_to_cpu(rm->ts_low));

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += cfd->len;

	return 0;
}