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
struct txdone_entry_desc {int retry; scalar_t__ flags; } ;
struct rt2x00_dev {TYPE_1__* tx; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {int /*<<< orphan*/  entry_idx; struct queue_entry_priv_mmio* priv_data; } ;
struct data_queue {int limit; struct queue_entry* entries; } ;
struct TYPE_2__ {int limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 int /*<<< orphan*/  STA_CSR4 ; 
 int /*<<< orphan*/  STA_CSR4_PID_SUBTYPE ; 
 int /*<<< orphan*/  STA_CSR4_PID_TYPE ; 
 int /*<<< orphan*/  STA_CSR4_RETRY_COUNT ; 
 int /*<<< orphan*/  STA_CSR4_TX_RESULT ; 
 int /*<<< orphan*/  STA_CSR4_VALID ; 
 int /*<<< orphan*/  TXDONE_EXCESSIVE_RETRY ; 
 int /*<<< orphan*/  TXDONE_FAILURE ; 
 int /*<<< orphan*/  TXDONE_FALLBACK ; 
 int /*<<< orphan*/  TXDONE_SUCCESS ; 
 int /*<<< orphan*/  TXDONE_UNKNOWN ; 
 int /*<<< orphan*/  TXD_W0_OWNER_NIC ; 
 int /*<<< orphan*/  TXD_W0_VALID ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_txdone (struct queue_entry*,struct txdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00lib_txdone_noinfo (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 
 struct data_queue* rt2x00queue_get_tx_queue (struct rt2x00_dev*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rt61pci_txdone(struct rt2x00_dev *rt2x00dev)
{
	struct data_queue *queue;
	struct queue_entry *entry;
	struct queue_entry *entry_done;
	struct queue_entry_priv_mmio *entry_priv;
	struct txdone_entry_desc txdesc;
	u32 word;
	u32 reg;
	int type;
	int index;
	int i;

	/*
	 * TX_STA_FIFO is a stack of X entries, hence read TX_STA_FIFO
	 * at most X times and also stop processing once the TX_STA_FIFO_VALID
	 * flag is not set anymore.
	 *
	 * The legacy drivers use X=TX_RING_SIZE but state in a comment
	 * that the TX_STA_FIFO stack has a size of 16. We stick to our
	 * tx ring size for now.
	 */
	for (i = 0; i < rt2x00dev->tx->limit; i++) {
		reg = rt2x00mmio_register_read(rt2x00dev, STA_CSR4);
		if (!rt2x00_get_field32(reg, STA_CSR4_VALID))
			break;

		/*
		 * Skip this entry when it contains an invalid
		 * queue identication number.
		 */
		type = rt2x00_get_field32(reg, STA_CSR4_PID_TYPE);
		queue = rt2x00queue_get_tx_queue(rt2x00dev, type);
		if (unlikely(!queue))
			continue;

		/*
		 * Skip this entry when it contains an invalid
		 * index number.
		 */
		index = rt2x00_get_field32(reg, STA_CSR4_PID_SUBTYPE);
		if (unlikely(index >= queue->limit))
			continue;

		entry = &queue->entries[index];
		entry_priv = entry->priv_data;
		word = rt2x00_desc_read(entry_priv->desc, 0);

		if (rt2x00_get_field32(word, TXD_W0_OWNER_NIC) ||
		    !rt2x00_get_field32(word, TXD_W0_VALID))
			return;

		entry_done = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		while (entry != entry_done) {
			/* Catch up.
			 * Just report any entries we missed as failed.
			 */
			rt2x00_warn(rt2x00dev, "TX status report missed for entry %d\n",
				    entry_done->entry_idx);

			rt2x00lib_txdone_noinfo(entry_done, TXDONE_UNKNOWN);
			entry_done = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		}

		/*
		 * Obtain the status about this packet.
		 */
		txdesc.flags = 0;
		switch (rt2x00_get_field32(reg, STA_CSR4_TX_RESULT)) {
		case 0: /* Success, maybe with retry */
			__set_bit(TXDONE_SUCCESS, &txdesc.flags);
			break;
		case 6: /* Failure, excessive retries */
			__set_bit(TXDONE_EXCESSIVE_RETRY, &txdesc.flags);
			/* Fall through - this is a failed frame! */
		default: /* Failure */
			__set_bit(TXDONE_FAILURE, &txdesc.flags);
		}
		txdesc.retry = rt2x00_get_field32(reg, STA_CSR4_RETRY_COUNT);

		/*
		 * the frame was retried at least once
		 * -> hw used fallback rates
		 */
		if (txdesc.retry)
			__set_bit(TXDONE_FALLBACK, &txdesc.flags);

		rt2x00lib_txdone(entry, &txdesc);
	}
}