#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct peak_usb_device {struct net_device* netdev; } ;
struct net_device_stats {int tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_dlc; int can_id; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_ERR_MASK ; 
 int CAN_RTR_FLAG ; 
 int PCAN_USB_MSG_HEADER_LEN ; 
 int PCAN_USB_STATUSLEN_EXT_ID ; 
 int PCAN_USB_STATUSLEN_RTR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pcan_usb_encode_msg(struct peak_usb_device *dev, struct sk_buff *skb,
			       u8 *obuf, size_t *size)
{
	struct net_device *netdev = dev->netdev;
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf = (struct can_frame *)skb->data;
	u8 *pc;

	obuf[0] = 2;
	obuf[1] = 1;

	pc = obuf + PCAN_USB_MSG_HEADER_LEN;

	/* status/len byte */
	*pc = cf->can_dlc;
	if (cf->can_id & CAN_RTR_FLAG)
		*pc |= PCAN_USB_STATUSLEN_RTR;

	/* can id */
	if (cf->can_id & CAN_EFF_FLAG) {
		__le32 tmp32 = cpu_to_le32((cf->can_id & CAN_ERR_MASK) << 3);

		*pc |= PCAN_USB_STATUSLEN_EXT_ID;
		memcpy(++pc, &tmp32, 4);
		pc += 4;
	} else {
		__le16 tmp16 = cpu_to_le16((cf->can_id & CAN_ERR_MASK) << 5);

		memcpy(++pc, &tmp16, 2);
		pc += 2;
	}

	/* can data */
	if (!(cf->can_id & CAN_RTR_FLAG)) {
		memcpy(pc, cf->data, cf->can_dlc);
		pc += cf->can_dlc;
	}

	obuf[(*size)-1] = (u8)(stats->tx_packets & 0xff);

	return 0;
}