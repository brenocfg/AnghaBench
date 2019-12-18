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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ data; } ;
struct pucan_tx_msg {void* size; int /*<<< orphan*/  d; int /*<<< orphan*/  channel_dlc; void* flags; void* can_id; void* type; } ;
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; } ;
struct canfd_frame {int can_id; int flags; scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t ALIGN (scalar_t__,int) ; 
 int CANFD_BRS ; 
 int CANFD_ESI ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 size_t PUCAN_MSG_BITRATE_SWITCH ; 
 size_t PUCAN_MSG_CAN_TX ; 
 int /*<<< orphan*/  PUCAN_MSG_CHANNEL_DLC (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t PUCAN_MSG_ERROR_STATE_IND ; 
 size_t PUCAN_MSG_EXT_DATA_LEN ; 
 size_t PUCAN_MSG_EXT_ID ; 
 size_t PUCAN_MSG_RTR ; 
 scalar_t__ can_is_canfd_skb (struct sk_buff*) ; 
 scalar_t__ can_len2dlc (scalar_t__) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pcan_usb_fd_encode_msg(struct peak_usb_device *dev,
				  struct sk_buff *skb, u8 *obuf, size_t *size)
{
	struct pucan_tx_msg *tx_msg = (struct pucan_tx_msg *)obuf;
	struct canfd_frame *cfd = (struct canfd_frame *)skb->data;
	u16 tx_msg_size, tx_msg_flags;
	u8 can_dlc;

	tx_msg_size = ALIGN(sizeof(struct pucan_tx_msg) + cfd->len, 4);
	tx_msg->size = cpu_to_le16(tx_msg_size);
	tx_msg->type = cpu_to_le16(PUCAN_MSG_CAN_TX);

	tx_msg_flags = 0;
	if (cfd->can_id & CAN_EFF_FLAG) {
		tx_msg_flags |= PUCAN_MSG_EXT_ID;
		tx_msg->can_id = cpu_to_le32(cfd->can_id & CAN_EFF_MASK);
	} else {
		tx_msg->can_id = cpu_to_le32(cfd->can_id & CAN_SFF_MASK);
	}

	if (can_is_canfd_skb(skb)) {
		/* considering a CANFD frame */
		can_dlc = can_len2dlc(cfd->len);

		tx_msg_flags |= PUCAN_MSG_EXT_DATA_LEN;

		if (cfd->flags & CANFD_BRS)
			tx_msg_flags |= PUCAN_MSG_BITRATE_SWITCH;

		if (cfd->flags & CANFD_ESI)
			tx_msg_flags |= PUCAN_MSG_ERROR_STATE_IND;
	} else {
		/* CAND 2.0 frames */
		can_dlc = cfd->len;

		if (cfd->can_id & CAN_RTR_FLAG)
			tx_msg_flags |= PUCAN_MSG_RTR;
	}

	tx_msg->flags = cpu_to_le16(tx_msg_flags);
	tx_msg->channel_dlc = PUCAN_MSG_CHANNEL_DLC(dev->ctrl_idx, can_dlc);
	memcpy(tx_msg->d, cfd->data, cfd->len);

	/* add null size message to tag the end (messages are 32-bits aligned)
	 */
	tx_msg = (struct pucan_tx_msg *)(obuf + tx_msg_size);

	tx_msg->size = 0;

	/* set the whole size of the USB packet to send */
	*size = tx_msg_size + sizeof(u32);

	return 0;
}