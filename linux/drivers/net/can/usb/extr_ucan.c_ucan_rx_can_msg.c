#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ctrlmode; } ;
struct ucan_priv {TYPE_4__* netdev; TYPE_1__ can; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_3__ can_msg; } ;
struct ucan_message_in {TYPE_2__ msg; int /*<<< orphan*/  len; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/  data; } ;
typedef  int canid_t ;
struct TYPE_9__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_ERR_FLAG ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int UCAN_IN_HDR_SIZE ; 
 struct sk_buff* alloc_can_skb (TYPE_4__*,struct can_frame**) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_4__*,char*,int,...) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ ucan_get_can_dlc (TYPE_3__*,int) ; 
 int ucan_handle_error_frame (struct ucan_priv*,struct ucan_message_in*,int) ; 

__attribute__((used)) static void ucan_rx_can_msg(struct ucan_priv *up, struct ucan_message_in *m)
{
	int len;
	canid_t canid;
	struct can_frame *cf;
	struct sk_buff *skb;
	struct net_device_stats *stats = &up->netdev->stats;

	/* get the contents of the length field */
	len = le16_to_cpu(m->len);

	/* check sanity */
	if (len < UCAN_IN_HDR_SIZE + sizeof(m->msg.can_msg.id)) {
		netdev_warn(up->netdev, "invalid input message len: %d\n", len);
		return;
	}

	/* handle error frames */
	canid = le32_to_cpu(m->msg.can_msg.id);
	if (canid & CAN_ERR_FLAG) {
		bool busstate_changed = ucan_handle_error_frame(up, m, canid);

		/* if berr-reporting is off only state changes get through */
		if (!(up->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) &&
		    !busstate_changed)
			return;
	} else {
		canid_t canid_mask;
		/* compute the mask for canid */
		canid_mask = CAN_RTR_FLAG;
		if (canid & CAN_EFF_FLAG)
			canid_mask |= CAN_EFF_MASK | CAN_EFF_FLAG;
		else
			canid_mask |= CAN_SFF_MASK;

		if (canid & ~canid_mask)
			netdev_warn(up->netdev,
				    "unexpected bits set (canid %x, mask %x)",
				    canid, canid_mask);

		canid &= canid_mask;
	}

	/* allocate skb */
	skb = alloc_can_skb(up->netdev, &cf);
	if (!skb)
		return;

	/* fill the can frame */
	cf->can_id = canid;

	/* compute DLC taking RTR_FLAG into account */
	cf->can_dlc = ucan_get_can_dlc(&m->msg.can_msg, len);

	/* copy the payload of non RTR frames */
	if (!(cf->can_id & CAN_RTR_FLAG) || (cf->can_id & CAN_ERR_FLAG))
		memcpy(cf->data, m->msg.can_msg.data, cf->can_dlc);

	/* don't count error frames as real packets */
	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;

	/* pass it to Linux */
	netif_rx(skb);
}