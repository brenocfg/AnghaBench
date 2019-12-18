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
typedef  int /*<<< orphan*/  u32 ;
struct skb_frame_desc {int /*<<< orphan*/  desc_len; int /*<<< orphan*/  desc; } ;
struct rxdone_entry_desc {int cipher_status; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  flags; } ;
struct queue_entry {TYPE_2__* skb; TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {int data_size; int /*<<< orphan*/  rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXDONE_L2PAD ; 
 int /*<<< orphan*/  RXDONE_MY_BSS ; 
 int /*<<< orphan*/  RXD_W0_CIPHER_ERROR ; 
 int /*<<< orphan*/  RXD_W0_CRC_ERROR ; 
 int /*<<< orphan*/  RXD_W0_DECRYPTED ; 
 int /*<<< orphan*/  RXD_W0_L2PAD ; 
 int /*<<< orphan*/  RXD_W0_MY_BSS ; 
 int /*<<< orphan*/  RXINFO_DESC_SIZE ; 
 int /*<<< orphan*/  RXINFO_W0_USB_DMA_RX_PKT_LEN ; 
 int RX_CRYPTO_FAIL_MIC ; 
 int RX_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_process_rxwi (struct queue_entry*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (int /*<<< orphan*/ ,char*,int) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (TYPE_2__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rt2800usb_fill_rxdone(struct queue_entry *entry,
				  struct rxdone_entry_desc *rxdesc)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *rxi = (__le32 *)entry->skb->data;
	__le32 *rxd;
	u32 word;
	int rx_pkt_len;

	/*
	 * Copy descriptor to the skbdesc->desc buffer, making it safe from
	 * moving of frame data in rt2x00usb.
	 */
	memcpy(skbdesc->desc, rxi, skbdesc->desc_len);

	/*
	 * RX frame format is :
	 * | RXINFO | RXWI | header | L2 pad | payload | pad | RXD | USB pad |
	 *          |<------------ rx_pkt_len -------------->|
	 */
	word = rt2x00_desc_read(rxi, 0);
	rx_pkt_len = rt2x00_get_field32(word, RXINFO_W0_USB_DMA_RX_PKT_LEN);

	/*
	 * Remove the RXINFO structure from the sbk.
	 */
	skb_pull(entry->skb, RXINFO_DESC_SIZE);

	/*
	 * Check for rx_pkt_len validity. Return if invalid, leaving
	 * rxdesc->size zeroed out by the upper level.
	 */
	if (unlikely(rx_pkt_len == 0 ||
			rx_pkt_len > entry->queue->data_size)) {
		rt2x00_err(entry->queue->rt2x00dev,
			   "Bad frame size %d, forcing to 0\n", rx_pkt_len);
		return;
	}

	rxd = (__le32 *)(entry->skb->data + rx_pkt_len);

	/*
	 * It is now safe to read the descriptor on all architectures.
	 */
	word = rt2x00_desc_read(rxd, 0);

	if (rt2x00_get_field32(word, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	rxdesc->cipher_status = rt2x00_get_field32(word, RXD_W0_CIPHER_ERROR);

	if (rt2x00_get_field32(word, RXD_W0_DECRYPTED)) {
		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. Unfortunately the descriptor doesn't contain
		 * any fields with the EIV/IV data either, so they can't
		 * be restored by rt2x00lib.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has already checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		if (rxdesc->cipher_status == RX_CRYPTO_SUCCESS) {
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		} else if (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC) {
			/*
			 * In order to check the Michael Mic, the packet must have
			 * been decrypted.  Mac80211 doesnt check the MMIC failure
			 * flag to initiate MMIC countermeasures if the decoded flag
			 * has not been set.
			 */
			rxdesc->flags |= RX_FLAG_DECRYPTED;

			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
		}
	}

	if (rt2x00_get_field32(word, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	if (rt2x00_get_field32(word, RXD_W0_L2PAD))
		rxdesc->dev_flags |= RXDONE_L2PAD;

	/*
	 * Remove RXD descriptor from end of buffer.
	 */
	skb_trim(entry->skb, rx_pkt_len);

	/*
	 * Process the RXWI structure.
	 */
	rt2800_process_rxwi(entry, rxdesc);
}