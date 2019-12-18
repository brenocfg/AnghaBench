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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct hif_device_usb {int rx_remain_len; int rx_transfer_len; int /*<<< orphan*/  htc_handle; TYPE_1__* udev; int /*<<< orphan*/  rx_lock; struct sk_buff* remain_skb; scalar_t__ rx_pad_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATH_USB_RX_STREAM_MODE_TAG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_PKT_NUM_IN_TRANSFER ; 
 int MAX_RX_BUF_SIZE ; 
 int /*<<< orphan*/  RX_STAT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RX_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_WLAN_RX_PIPE ; 
 struct sk_buff* __dev_alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_htc_rx_msg (int /*<<< orphan*/ ,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_allocated ; 
 int /*<<< orphan*/  skb_completed ; 
 int /*<<< orphan*/  skb_completed_bytes ; 
 int /*<<< orphan*/  skb_dropped ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_hif_usb_rx_stream(struct hif_device_usb *hif_dev,
				    struct sk_buff *skb)
{
	struct sk_buff *nskb, *skb_pool[MAX_PKT_NUM_IN_TRANSFER];
	int index = 0, i, len = skb->len;
	int rx_remain_len, rx_pkt_len;
	u16 pool_index = 0;
	u8 *ptr;

	spin_lock(&hif_dev->rx_lock);

	rx_remain_len = hif_dev->rx_remain_len;
	rx_pkt_len = hif_dev->rx_transfer_len;

	if (rx_remain_len != 0) {
		struct sk_buff *remain_skb = hif_dev->remain_skb;

		if (remain_skb) {
			ptr = (u8 *) remain_skb->data;

			index = rx_remain_len;
			rx_remain_len -= hif_dev->rx_pad_len;
			ptr += rx_pkt_len;

			memcpy(ptr, skb->data, rx_remain_len);

			rx_pkt_len += rx_remain_len;
			hif_dev->rx_remain_len = 0;
			skb_put(remain_skb, rx_pkt_len);

			skb_pool[pool_index++] = remain_skb;

		} else {
			index = rx_remain_len;
		}
	}

	spin_unlock(&hif_dev->rx_lock);

	while (index < len) {
		u16 pkt_len;
		u16 pkt_tag;
		u16 pad_len;
		int chk_idx;

		ptr = (u8 *) skb->data;

		pkt_len = get_unaligned_le16(ptr + index);
		pkt_tag = get_unaligned_le16(ptr + index + 2);

		if (pkt_tag != ATH_USB_RX_STREAM_MODE_TAG) {
			RX_STAT_INC(skb_dropped);
			return;
		}

		pad_len = 4 - (pkt_len & 0x3);
		if (pad_len == 4)
			pad_len = 0;

		chk_idx = index;
		index = index + 4 + pkt_len + pad_len;

		if (index > MAX_RX_BUF_SIZE) {
			spin_lock(&hif_dev->rx_lock);
			hif_dev->rx_remain_len = index - MAX_RX_BUF_SIZE;
			hif_dev->rx_transfer_len =
				MAX_RX_BUF_SIZE - chk_idx - 4;
			hif_dev->rx_pad_len = pad_len;

			nskb = __dev_alloc_skb(pkt_len + 32, GFP_ATOMIC);
			if (!nskb) {
				dev_err(&hif_dev->udev->dev,
					"ath9k_htc: RX memory allocation error\n");
				spin_unlock(&hif_dev->rx_lock);
				goto err;
			}
			skb_reserve(nskb, 32);
			RX_STAT_INC(skb_allocated);

			memcpy(nskb->data, &(skb->data[chk_idx+4]),
			       hif_dev->rx_transfer_len);

			/* Record the buffer pointer */
			hif_dev->remain_skb = nskb;
			spin_unlock(&hif_dev->rx_lock);
		} else {
			nskb = __dev_alloc_skb(pkt_len + 32, GFP_ATOMIC);
			if (!nskb) {
				dev_err(&hif_dev->udev->dev,
					"ath9k_htc: RX memory allocation error\n");
				goto err;
			}
			skb_reserve(nskb, 32);
			RX_STAT_INC(skb_allocated);

			memcpy(nskb->data, &(skb->data[chk_idx+4]), pkt_len);
			skb_put(nskb, pkt_len);
			skb_pool[pool_index++] = nskb;
		}
	}

err:
	for (i = 0; i < pool_index; i++) {
		RX_STAT_ADD(skb_completed_bytes, skb_pool[i]->len);
		ath9k_htc_rx_msg(hif_dev->htc_handle, skb_pool[i],
				 skb_pool[i]->len, USB_WLAN_RX_PIPE);
		RX_STAT_INC(skb_completed);
	}
}