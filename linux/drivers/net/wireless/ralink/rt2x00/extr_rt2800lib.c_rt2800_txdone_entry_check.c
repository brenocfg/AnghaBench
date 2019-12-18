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
struct queue_entry {int /*<<< orphan*/  entry_idx; TYPE_1__* queue; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  qid; int /*<<< orphan*/  rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 int /*<<< orphan*/  TXWI_W1_ACK ; 
 int /*<<< orphan*/  TXWI_W1_PACKETID ; 
 int /*<<< orphan*/  TXWI_W1_WIRELESS_CLI_ID ; 
 int /*<<< orphan*/  TX_STA_FIFO_PID_TYPE ; 
 int /*<<< orphan*/  TX_STA_FIFO_TX_ACK_REQUIRED ; 
 int /*<<< orphan*/  TX_STA_FIFO_TX_AGGRE ; 
 int /*<<< orphan*/  TX_STA_FIFO_WCID ; 
 int /*<<< orphan*/ * rt2800_drv_get_txwi (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rt2800_txdone_entry_check(struct queue_entry *entry, u32 reg)
{
	__le32 *txwi;
	u32 word;
	int wcid, ack, pid;
	int tx_wcid, tx_ack, tx_pid, is_agg;

	/*
	 * This frames has returned with an IO error,
	 * so the status report is not intended for this
	 * frame.
	 */
	if (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		return false;

	wcid	= rt2x00_get_field32(reg, TX_STA_FIFO_WCID);
	ack	= rt2x00_get_field32(reg, TX_STA_FIFO_TX_ACK_REQUIRED);
	pid	= rt2x00_get_field32(reg, TX_STA_FIFO_PID_TYPE);
	is_agg	= rt2x00_get_field32(reg, TX_STA_FIFO_TX_AGGRE);

	/*
	 * Validate if this TX status report is intended for
	 * this entry by comparing the WCID/ACK/PID fields.
	 */
	txwi = rt2800_drv_get_txwi(entry);

	word = rt2x00_desc_read(txwi, 1);
	tx_wcid = rt2x00_get_field32(word, TXWI_W1_WIRELESS_CLI_ID);
	tx_ack  = rt2x00_get_field32(word, TXWI_W1_ACK);
	tx_pid  = rt2x00_get_field32(word, TXWI_W1_PACKETID);

	if (wcid != tx_wcid || ack != tx_ack || (!is_agg && pid != tx_pid)) {
		rt2x00_dbg(entry->queue->rt2x00dev,
			   "TX status report missed for queue %d entry %d\n",
			   entry->queue->qid, entry->entry_idx);
		return false;
	}

	return true;
}