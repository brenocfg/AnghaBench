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
typedef  int u16 ;
struct txdone_entry_desc {int retry; scalar_t__ flags; } ;
struct skb_frame_desc {int /*<<< orphan*/ * sta; } ;
struct rt2x00_dev {int long_retry; int /*<<< orphan*/  curr_band; struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int /*<<< orphan*/ ** wcid_to_sta; } ;
struct queue_entry {int /*<<< orphan*/  skb; TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXDONE_AMPDU ; 
 int /*<<< orphan*/  TXDONE_FAILURE ; 
 int /*<<< orphan*/  TXDONE_FALLBACK ; 
 int /*<<< orphan*/  TXDONE_NO_ACK_REQ ; 
 int /*<<< orphan*/  TXDONE_SUCCESS ; 
 int /*<<< orphan*/  TXWI_W0_AMPDU ; 
 int /*<<< orphan*/  TXWI_W0_MCS ; 
 int /*<<< orphan*/  TX_STA_FIFO_MCS ; 
 int /*<<< orphan*/  TX_STA_FIFO_TX_ACK_REQUIRED ; 
 int /*<<< orphan*/  TX_STA_FIFO_TX_AGGRE ; 
 int /*<<< orphan*/  TX_STA_FIFO_TX_SUCCESS ; 
 int /*<<< orphan*/  TX_STA_FIFO_WCID ; 
 int WCID_END ; 
 int WCID_START ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rt2800_rate_from_status (struct skb_frame_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_txdone (struct queue_entry*,struct txdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00lib_txdone_nomatch (struct queue_entry*,struct txdone_entry_desc*) ; 
 scalar_t__ unlikely (int) ; 

void rt2800_txdone_entry(struct queue_entry *entry, u32 status, __le32 *txwi,
			 bool match)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	struct txdone_entry_desc txdesc;
	u32 word;
	u16 mcs, real_mcs;
	int aggr, ampdu, wcid, ack_req;

	/*
	 * Obtain the status about this packet.
	 */
	txdesc.flags = 0;
	word = rt2x00_desc_read(txwi, 0);

	mcs = rt2x00_get_field32(word, TXWI_W0_MCS);
	ampdu = rt2x00_get_field32(word, TXWI_W0_AMPDU);

	real_mcs = rt2x00_get_field32(status, TX_STA_FIFO_MCS);
	aggr = rt2x00_get_field32(status, TX_STA_FIFO_TX_AGGRE);
	wcid = rt2x00_get_field32(status, TX_STA_FIFO_WCID);
	ack_req	= rt2x00_get_field32(status, TX_STA_FIFO_TX_ACK_REQUIRED);

	/*
	 * If a frame was meant to be sent as a single non-aggregated MPDU
	 * but ended up in an aggregate the used tx rate doesn't correlate
	 * with the one specified in the TXWI as the whole aggregate is sent
	 * with the same rate.
	 *
	 * For example: two frames are sent to rt2x00, the first one sets
	 * AMPDU=1 and requests MCS7 whereas the second frame sets AMDPU=0
	 * and requests MCS15. If the hw aggregates both frames into one
	 * AMDPU the tx status for both frames will contain MCS7 although
	 * the frame was sent successfully.
	 *
	 * Hence, replace the requested rate with the real tx rate to not
	 * confuse the rate control algortihm by providing clearly wrong
	 * data.
	 *
	 * FIXME: if we do not find matching entry, we tell that frame was
	 * posted without any retries. We need to find a way to fix that
	 * and provide retry count.
 	 */
	if (unlikely((aggr == 1 && ampdu == 0 && real_mcs != mcs)) || !match) {
		rt2800_rate_from_status(skbdesc, status, rt2x00dev->curr_band);
		mcs = real_mcs;
	}

	if (aggr == 1 || ampdu == 1)
		__set_bit(TXDONE_AMPDU, &txdesc.flags);

	if (!ack_req)
		__set_bit(TXDONE_NO_ACK_REQ, &txdesc.flags);

	/*
	 * Ralink has a retry mechanism using a global fallback
	 * table. We setup this fallback table to try the immediate
	 * lower rate for all rates. In the TX_STA_FIFO, the MCS field
	 * always contains the MCS used for the last transmission, be
	 * it successful or not.
	 */
	if (rt2x00_get_field32(status, TX_STA_FIFO_TX_SUCCESS)) {
		/*
		 * Transmission succeeded. The number of retries is
		 * mcs - real_mcs
		 */
		__set_bit(TXDONE_SUCCESS, &txdesc.flags);
		txdesc.retry = ((mcs > real_mcs) ? mcs - real_mcs : 0);
	} else {
		/*
		 * Transmission failed. The number of retries is
		 * always 7 in this case (for a total number of 8
		 * frames sent).
		 */
		__set_bit(TXDONE_FAILURE, &txdesc.flags);
		txdesc.retry = rt2x00dev->long_retry;
	}

	/*
	 * the frame was retried at least once
	 * -> hw used fallback rates
	 */
	if (txdesc.retry)
		__set_bit(TXDONE_FALLBACK, &txdesc.flags);

	if (!match) {
		/* RCU assures non-null sta will not be freed by mac80211. */
		rcu_read_lock();
		if (likely(wcid >= WCID_START && wcid <= WCID_END))
			skbdesc->sta = drv_data->wcid_to_sta[wcid - WCID_START];
		else
			skbdesc->sta = NULL;
		rt2x00lib_txdone_nomatch(entry, &txdesc);
		rcu_read_unlock();
	} else {
		rt2x00lib_txdone(entry, &txdesc);
	}
}