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
typedef  int /*<<< orphan*/  u32 ;
struct skb_frame_desc {int skb_dma; } ;
struct rt2x00_dev {int /*<<< orphan*/  txstatus_timer; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {TYPE_1__* queue; int /*<<< orphan*/  entry_idx; int /*<<< orphan*/  skb; struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_2__ {scalar_t__ qid; int length; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 scalar_t__ QID_RX ; 
 int /*<<< orphan*/  RXD_W0_SDP0 ; 
 int /*<<< orphan*/  RXD_W1_DMA_DONE ; 
 int /*<<< orphan*/  RX_CRX_IDX ; 
 int /*<<< orphan*/  TXD_W1_DMA_DONE ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800mmio_clear_entry(struct queue_entry *entry)
{
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 word;

	if (entry->queue->qid == QID_RX) {
		word = rt2x00_desc_read(entry_priv->desc, 0);
		rt2x00_set_field32(&word, RXD_W0_SDP0, skbdesc->skb_dma);
		rt2x00_desc_write(entry_priv->desc, 0, word);

		word = rt2x00_desc_read(entry_priv->desc, 1);
		rt2x00_set_field32(&word, RXD_W1_DMA_DONE, 0);
		rt2x00_desc_write(entry_priv->desc, 1, word);

		/*
		 * Set RX IDX in register to inform hardware that we have
		 * handled this entry and it is available for reuse again.
		 */
		rt2x00mmio_register_write(rt2x00dev, RX_CRX_IDX,
					  entry->entry_idx);
	} else {
		word = rt2x00_desc_read(entry_priv->desc, 1);
		rt2x00_set_field32(&word, TXD_W1_DMA_DONE, 1);
		rt2x00_desc_write(entry_priv->desc, 1, word);

		/* If last entry stop txstatus timer */
		if (entry->queue->length == 1)
			hrtimer_cancel(&rt2x00dev->txstatus_timer);
	}
}