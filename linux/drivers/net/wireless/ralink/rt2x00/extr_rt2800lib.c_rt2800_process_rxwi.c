#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rxdone_entry_desc {int signal; scalar_t__ rate_mode; int /*<<< orphan*/  rssi; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  enc_flags; void* size; void* cipher; } ;
struct queue_entry {TYPE_1__* queue; TYPE_2__* skb; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  winfo_size; int /*<<< orphan*/  rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 scalar_t__ RATE_MODE_CCK ; 
 int /*<<< orphan*/  RXDONE_SIGNAL_MCS ; 
 int /*<<< orphan*/  RXWI_W0_MPDU_TOTAL_BYTE_COUNT ; 
 int /*<<< orphan*/  RXWI_W0_UDF ; 
 int /*<<< orphan*/  RXWI_W1_BW ; 
 int /*<<< orphan*/  RXWI_W1_MCS ; 
 int /*<<< orphan*/  RXWI_W1_PHYMODE ; 
 int /*<<< orphan*/  RXWI_W1_SHORT_GI ; 
 int /*<<< orphan*/  RX_ENC_FLAG_SHORT_GI ; 
 int /*<<< orphan*/  rt2800_agc_to_rssi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 void* rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_2__*,int /*<<< orphan*/ ) ; 

void rt2800_process_rxwi(struct queue_entry *entry,
			 struct rxdone_entry_desc *rxdesc)
{
	__le32 *rxwi = (__le32 *) entry->skb->data;
	u32 word;

	word = rt2x00_desc_read(rxwi, 0);

	rxdesc->cipher = rt2x00_get_field32(word, RXWI_W0_UDF);
	rxdesc->size = rt2x00_get_field32(word, RXWI_W0_MPDU_TOTAL_BYTE_COUNT);

	word = rt2x00_desc_read(rxwi, 1);

	if (rt2x00_get_field32(word, RXWI_W1_SHORT_GI))
		rxdesc->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	if (rt2x00_get_field32(word, RXWI_W1_BW))
		rxdesc->bw = RATE_INFO_BW_40;

	/*
	 * Detect RX rate, always use MCS as signal type.
	 */
	rxdesc->dev_flags |= RXDONE_SIGNAL_MCS;
	rxdesc->signal = rt2x00_get_field32(word, RXWI_W1_MCS);
	rxdesc->rate_mode = rt2x00_get_field32(word, RXWI_W1_PHYMODE);

	/*
	 * Mask of 0x8 bit to remove the short preamble flag.
	 */
	if (rxdesc->rate_mode == RATE_MODE_CCK)
		rxdesc->signal &= ~0x8;

	word = rt2x00_desc_read(rxwi, 2);

	/*
	 * Convert descriptor AGC value to RSSI value.
	 */
	rxdesc->rssi = rt2800_agc_to_rssi(entry->queue->rt2x00dev, word);
	/*
	 * Remove RXWI descriptor from start of the buffer.
	 */
	skb_pull(entry->skb, entry->queue->winfo_size);
}