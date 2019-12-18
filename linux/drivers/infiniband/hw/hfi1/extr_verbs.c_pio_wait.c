#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct send_context {int /*<<< orphan*/  waitlock; int /*<<< orphan*/  piowait; struct hfi1_devdata* dd; } ;
struct rvt_qp {size_t state; int s_flags; int /*<<< orphan*/  s_lock; struct hfi1_qp_priv* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  list; } ;
struct hfi1_qp_priv {TYPE_3__ s_iowait; } ;
struct hfi1_pkt_state {TYPE_5__* wait; int /*<<< orphan*/  pkts_sent; TYPE_2__* s_txreq; } ;
struct hfi1_ibdev {int n_piowait; int n_piodrain; } ;
struct hfi1_devdata {struct hfi1_ibdev verbs_dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_head; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_7__ {TYPE_1__ txreq; } ;

/* Variables and functions */
 int EBUSY ; 
 int HFI1_S_WAIT_PIO_DRAIN ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_S_WAIT_PIO ; 
 int /*<<< orphan*/  hfi1_qp_unbusy (struct rvt_qp*,TYPE_5__*) ; 
 int /*<<< orphan*/  hfi1_sc_wantpiobuf_intr (struct send_context*,int) ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  iowait_get_priority (TYPE_3__*) ; 
 int /*<<< orphan*/  iowait_queue (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_hfi1_qpsleep (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pio_wait(struct rvt_qp *qp,
		    struct send_context *sc,
		    struct hfi1_pkt_state *ps,
		    u32 flag)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct hfi1_devdata *dd = sc->dd;
	unsigned long flags;
	int ret = 0;

	/*
	 * Note that as soon as want_buffer() is called and
	 * possibly before it returns, sc_piobufavail()
	 * could be called. Therefore, put QP on the I/O wait list before
	 * enabling the PIO avail interrupt.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	if (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) {
		write_seqlock(&sc->waitlock);
		list_add_tail(&ps->s_txreq->txreq.list,
			      &ps->wait->tx_head);
		if (list_empty(&priv->s_iowait.list)) {
			struct hfi1_ibdev *dev = &dd->verbs_dev;
			int was_empty;

			dev->n_piowait += !!(flag & RVT_S_WAIT_PIO);
			dev->n_piodrain += !!(flag & HFI1_S_WAIT_PIO_DRAIN);
			qp->s_flags |= flag;
			was_empty = list_empty(&sc->piowait);
			iowait_get_priority(&priv->s_iowait);
			iowait_queue(ps->pkts_sent, &priv->s_iowait,
				     &sc->piowait);
			priv->s_iowait.lock = &sc->waitlock;
			trace_hfi1_qpsleep(qp, RVT_S_WAIT_PIO);
			rvt_get_qp(qp);
			/* counting: only call wantpiobuf_intr if first user */
			if (was_empty)
				hfi1_sc_wantpiobuf_intr(sc, 1);
		}
		write_sequnlock(&sc->waitlock);
		hfi1_qp_unbusy(qp, ps->wait);
		ret = -EBUSY;
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);
	return ret;
}