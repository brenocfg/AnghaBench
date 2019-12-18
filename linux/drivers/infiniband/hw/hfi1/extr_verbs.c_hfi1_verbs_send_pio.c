#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct send_context {int dummy; } ;
struct TYPE_12__ {void* vaddr; } ;
struct rvt_sge_state {TYPE_4__ sge; } ;
struct TYPE_9__ {int qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {int /*<<< orphan*/  s_lock; TYPE_1__ ibqp; scalar_t__ s_wqe; int /*<<< orphan*/  srate_mbps; struct hfi1_qp_priv* priv; } ;
struct pio_buf {int dummy; } ;
struct hfi1_qp_priv {int s_sc; int /*<<< orphan*/  s_iowait; } ;
struct hfi1_pportdata {TYPE_5__* dd; } ;
struct hfi1_pkt_state {TYPE_8__* s_txreq; int /*<<< orphan*/  opcode; struct hfi1_pportdata* ppd; } ;
typedef  int /*<<< orphan*/  (* pio_release_cb ) (struct rvt_qp*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  pbc ;
struct TYPE_11__ {scalar_t__ hdr_type; int /*<<< orphan*/  ibh; int /*<<< orphan*/  opah; } ;
struct TYPE_10__ {TYPE_3__ hdr; } ;
struct TYPE_14__ {int hdr_dwords; int s_cur_size; TYPE_2__ phdr; struct send_context* psc; struct rvt_sge_state* ss; } ;
struct TYPE_13__ {void* sdma_pad_dma; } ;

/* Variables and functions */
#define  IB_QPT_RC 129 
#define  IB_QPT_UC 128 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_SUCCESS ; 
 scalar_t__ IS_ERR (struct pio_buf*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct pio_buf*) ; 
 int PBC_DC_INFO_SHIFT ; 
 int PBC_INSERT_BYPASS_ICRC ; 
 int PBC_PACKET_BYPASS ; 
 int /*<<< orphan*/  PIO ; 
 int /*<<< orphan*/  RVT_S_WAIT_PIO ; 
 int SIZE_OF_CRC ; 
 int SIZE_OF_LT ; 
 int create_pbc (struct hfi1_pportdata*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dd_from_ibdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*) ; 
 int hfi1_dbg_should_fault_tx (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int hfi1_fault_tx (struct rvt_qp*,int /*<<< orphan*/ ,int) ; 
 int hfi1_get_16b_padding (int,int) ; 
 int /*<<< orphan*/  hfi1_put_txreq (TYPE_8__*) ; 
 int /*<<< orphan*/  hfi1_rc_send_complete (struct rvt_qp*,TYPE_3__*) ; 
 int /*<<< orphan*/  hfi1_rc_verbs_aborted (struct rvt_qp*,TYPE_3__*) ; 
 int ib_is_sc5 (int) ; 
 int /*<<< orphan*/  iowait_pio_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pio_copy (TYPE_5__*,struct pio_buf*,int,int*,int) ; 
 int pio_wait (struct rvt_qp*,struct send_context*,struct hfi1_pkt_state*,int /*<<< orphan*/ ) ; 
 int rvt_get_sge_length (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rvt_send_complete (struct rvt_qp*,scalar_t__,int) ; 
 int /*<<< orphan*/  rvt_update_sge (struct rvt_sge_state*,int,int) ; 
 struct pio_buf* sc_buffer_alloc (struct send_context*,int,int /*<<< orphan*/  (*) (struct rvt_qp*,int /*<<< orphan*/ ),struct rvt_qp*) ; 
 int sc_to_vlt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seg_pio_copy_end (struct pio_buf*) ; 
 int /*<<< orphan*/  seg_pio_copy_mid (struct pio_buf*,void*,int) ; 
 int /*<<< orphan*/  seg_pio_copy_start (struct pio_buf*,int,int*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_pio_output_ibhdr (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ unlikely (int) ; 
 int update_hcrc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_tx_opstats (struct rvt_qp*,struct hfi1_pkt_state*,int) ; 
 int /*<<< orphan*/  verbs_pio_complete (struct rvt_qp*,int /*<<< orphan*/ ) ; 

int hfi1_verbs_send_pio(struct rvt_qp *qp, struct hfi1_pkt_state *ps,
			u64 pbc)
{
	struct hfi1_qp_priv *priv = qp->priv;
	u32 hdrwords = ps->s_txreq->hdr_dwords;
	struct rvt_sge_state *ss = ps->s_txreq->ss;
	u32 len = ps->s_txreq->s_cur_size;
	u32 dwords;
	u32 plen;
	struct hfi1_pportdata *ppd = ps->ppd;
	u32 *hdr;
	u8 sc5;
	unsigned long flags = 0;
	struct send_context *sc;
	struct pio_buf *pbuf;
	int wc_status = IB_WC_SUCCESS;
	int ret = 0;
	pio_release_cb cb = NULL;
	u8 extra_bytes = 0;

	if (ps->s_txreq->phdr.hdr.hdr_type) {
		u8 pad_size = hfi1_get_16b_padding((hdrwords << 2), len);

		extra_bytes = pad_size + (SIZE_OF_CRC << 2) + SIZE_OF_LT;
		dwords = (len + extra_bytes) >> 2;
		hdr = (u32 *)&ps->s_txreq->phdr.hdr.opah;
	} else {
		dwords = (len + 3) >> 2;
		hdr = (u32 *)&ps->s_txreq->phdr.hdr.ibh;
	}
	plen = hdrwords + dwords + sizeof(pbc) / 4;

	/* only RC/UC use complete */
	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
	case IB_QPT_UC:
		cb = verbs_pio_complete;
		break;
	default:
		break;
	}

	/* vl15 special case taken care of in ud.c */
	sc5 = priv->s_sc;
	sc = ps->s_txreq->psc;

	if (likely(pbc == 0)) {
		u8 vl = sc_to_vlt(dd_from_ibdev(qp->ibqp.device), sc5);

		/* set PBC_DC_INFO bit (aka SC[4]) in pbc */
		if (ps->s_txreq->phdr.hdr.hdr_type)
			pbc |= PBC_PACKET_BYPASS | PBC_INSERT_BYPASS_ICRC;
		else
			pbc |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);

		pbc = create_pbc(ppd, pbc, qp->srate_mbps, vl, plen);
		if (unlikely(hfi1_dbg_should_fault_tx(qp, ps->opcode)))
			pbc = hfi1_fault_tx(qp, ps->opcode, pbc);
		else
			/* Update HCRC based on packet opcode */
			pbc = update_hcrc(ps->opcode, pbc);
	}
	if (cb)
		iowait_pio_inc(&priv->s_iowait);
	pbuf = sc_buffer_alloc(sc, plen, cb, qp);
	if (IS_ERR_OR_NULL(pbuf)) {
		if (cb)
			verbs_pio_complete(qp, 0);
		if (IS_ERR(pbuf)) {
			/*
			 * If we have filled the PIO buffers to capacity and are
			 * not in an active state this request is not going to
			 * go out to so just complete it with an error or else a
			 * ULP or the core may be stuck waiting.
			 */
			hfi1_cdbg(
				PIO,
				"alloc failed. state not active, completing");
			wc_status = IB_WC_GENERAL_ERR;
			goto pio_bail;
		} else {
			/*
			 * This is a normal occurrence. The PIO buffs are full
			 * up but we are still happily sending, well we could be
			 * so lets continue to queue the request.
			 */
			hfi1_cdbg(PIO, "alloc failed. state active, queuing");
			ret = pio_wait(qp, sc, ps, RVT_S_WAIT_PIO);
			if (!ret)
				/* txreq not queued - free */
				goto bail;
			/* tx consumed in wait */
			return ret;
		}
	}

	if (dwords == 0) {
		pio_copy(ppd->dd, pbuf, pbc, hdr, hdrwords);
	} else {
		seg_pio_copy_start(pbuf, pbc,
				   hdr, hdrwords * 4);
		if (ss) {
			while (len) {
				void *addr = ss->sge.vaddr;
				u32 slen = rvt_get_sge_length(&ss->sge, len);

				rvt_update_sge(ss, slen, false);
				seg_pio_copy_mid(pbuf, addr, slen);
				len -= slen;
			}
		}
		/* add icrc, lt byte, and padding to flit */
		if (extra_bytes)
			seg_pio_copy_mid(pbuf, ppd->dd->sdma_pad_dma,
					 extra_bytes);

		seg_pio_copy_end(pbuf);
	}

	update_tx_opstats(qp, ps, plen);
	trace_pio_output_ibhdr(dd_from_ibdev(qp->ibqp.device),
			       &ps->s_txreq->phdr.hdr, ib_is_sc5(sc5));

pio_bail:
	spin_lock_irqsave(&qp->s_lock, flags);
	if (qp->s_wqe) {
		rvt_send_complete(qp, qp->s_wqe, wc_status);
	} else if (qp->ibqp.qp_type == IB_QPT_RC) {
		if (unlikely(wc_status == IB_WC_GENERAL_ERR))
			hfi1_rc_verbs_aborted(qp, &ps->s_txreq->phdr.hdr);
		hfi1_rc_send_complete(qp, &ps->s_txreq->phdr.hdr);
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);

	ret = 0;

bail:
	hfi1_put_txreq(ps->s_txreq);
	return ret;
}