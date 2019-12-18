#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {size_t pidx; int /*<<< orphan*/ * desc; } ;
struct sge_uld_txq {TYPE_3__ sendq; TYPE_1__ q; int /*<<< orphan*/  adap; scalar_t__ service_ofldq_running; scalar_t__ full; } ;
struct fw_wr_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 unsigned int MAX_IMM_OFLD_TX_DATA_WR_LEN ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int TXQ_STOP_THRES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cxgb4_ring_tx_db (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 unsigned int flits_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inline_tx_header (void const*,TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ofldtxq_stop (struct sge_uld_txq*,struct fw_wr_hdr*) ; 
 int /*<<< orphan*/  skb_queue_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txq_advance (TYPE_1__*,unsigned int) ; 
 unsigned int txq_avail (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ofld_xmit_direct(struct sge_uld_txq *q, const void *src,
			    unsigned int len)
{
	unsigned int ndesc;
	int credits;
	u64 *pos;

	/* Use the lower limit as the cut-off */
	if (len > MAX_IMM_OFLD_TX_DATA_WR_LEN) {
		WARN_ON(1);
		return NET_XMIT_DROP;
	}

	/* Don't return NET_XMIT_CN here as the current
	 * implementation doesn't queue the request
	 * using an skb when the following conditions not met
	 */
	if (!spin_trylock(&q->sendq.lock))
		return NET_XMIT_DROP;

	if (q->full || !skb_queue_empty(&q->sendq) ||
	    q->service_ofldq_running) {
		spin_unlock(&q->sendq.lock);
		return NET_XMIT_DROP;
	}
	ndesc = flits_to_desc(DIV_ROUND_UP(len, 8));
	credits = txq_avail(&q->q) - ndesc;
	pos = (u64 *)&q->q.desc[q->q.pidx];

	/* ofldtxq_stop modifies WR header in-situ */
	inline_tx_header(src, &q->q, pos, len);
	if (unlikely(credits < TXQ_STOP_THRES))
		ofldtxq_stop(q, (struct fw_wr_hdr *)pos);
	txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(q->adap, &q->q, ndesc);

	spin_unlock(&q->sendq.lock);
	return NET_XMIT_SUCCESS;
}