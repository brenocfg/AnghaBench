#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_18__ {int /*<<< orphan*/  sb_index; int /*<<< orphan*/  cache_line_log; int /*<<< orphan*/  sge_buf_sz; int /*<<< orphan*/  max_sge_pkt; int /*<<< orphan*/  tpa_agg_sz; int /*<<< orphan*/  buf_sz; int /*<<< orphan*/  rcq_np_addr; int /*<<< orphan*/  rcq_addr; int /*<<< orphan*/  sge_addr; int /*<<< orphan*/  rxq_addr; int /*<<< orphan*/  drop_flags; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  hc_rate; int /*<<< orphan*/  vf_sb; } ;
struct TYPE_15__ {int /*<<< orphan*/  traffic_type; int /*<<< orphan*/  sb_index; int /*<<< orphan*/  txq_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  hc_rate; int /*<<< orphan*/  vf_sb; } ;
struct vfpf_setup_q_tlv {scalar_t__ vf_qid; int param_valid; TYPE_9__ rxq; TYPE_6__ txq; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct TYPE_16__ {unsigned long flags; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  hc_rate; } ;
struct TYPE_14__ {unsigned long flags; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  hc_rate; } ;
struct bnx2x_queue_init_params {TYPE_7__ rx; TYPE_5__ tx; } ;
struct TYPE_12__ {struct bnx2x_queue_init_params init; } ;
struct TYPE_13__ {TYPE_3__ params; } ;
struct TYPE_17__ {int /*<<< orphan*/  mtu; } ;
struct bnx2x_rxq_setup_params {int /*<<< orphan*/  mcast_engine_id; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  cache_line_log; int /*<<< orphan*/  sge_buf_sz; int /*<<< orphan*/  max_sges_pkt; int /*<<< orphan*/  tpa_agg_sz; int /*<<< orphan*/  buf_sz; int /*<<< orphan*/  rcq_np_map; int /*<<< orphan*/  rcq_map; int /*<<< orphan*/  sge_map; int /*<<< orphan*/  dscr_map; int /*<<< orphan*/  drop_flags; } ;
struct bnx2x_txq_setup_params {int /*<<< orphan*/  traffic_type; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  dscr_map; } ;
struct bnx2x_queue_setup_params {unsigned long flags; TYPE_8__ gen_params; struct bnx2x_rxq_setup_params rxq_params; struct bnx2x_txq_setup_params txq_params; } ;
struct bnx2x_vf_queue_construct_params {TYPE_4__ qstate; struct bnx2x_queue_setup_params prep_qsetup; } ;
struct bnx2x_vf_queue {int /*<<< orphan*/  index; int /*<<< orphan*/  sb_idx; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x {int dummy; } ;
struct TYPE_10__ {struct vfpf_setup_q_tlv setup_q; } ;
struct TYPE_11__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_ACTIVE ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_MCAST ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_RX ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_TX ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int VFPF_RXQ_VALID ; 
 int VFPF_TXQ_VALID ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  bnx2x_leading_vfq_init (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_queue*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_set_q_flags (struct bnx2x*,int /*<<< orphan*/ ,unsigned long*) ; 
 int bnx2x_vf_queue_setup (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ,struct bnx2x_vf_queue_construct_params*) ; 
 int /*<<< orphan*/  bnx2x_vfop_qctor_dump_rx (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_queue_init_params*,struct bnx2x_queue_setup_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_qctor_dump_tx (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_queue_init_params*,struct bnx2x_queue_setup_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_qctor_prep (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_queue*,struct bnx2x_vf_queue_construct_params*,unsigned long) ; 
 scalar_t__ bnx2x_vfq_is_leading (struct bnx2x_vf_queue*) ; 
 int /*<<< orphan*/  memset (struct bnx2x_vf_queue_construct_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vf_rxq_count (struct bnx2x_virtf*) ; 
 struct bnx2x_vf_queue* vfq_get (struct bnx2x_virtf*,scalar_t__) ; 

__attribute__((used)) static void bnx2x_vf_mbx_setup_q(struct bnx2x *bp, struct bnx2x_virtf *vf,
				 struct bnx2x_vf_mbx *mbx)
{
	struct vfpf_setup_q_tlv *setup_q = &mbx->msg->req.setup_q;
	struct bnx2x_vf_queue_construct_params qctor;
	int rc = 0;

	/* verify vf_qid */
	if (setup_q->vf_qid >= vf_rxq_count(vf)) {
		BNX2X_ERR("vf_qid %d invalid, max queue count is %d\n",
			  setup_q->vf_qid, vf_rxq_count(vf));
		rc = -EINVAL;
		goto response;
	}

	/* tx queues must be setup alongside rx queues thus if the rx queue
	 * is not marked as valid there's nothing to do.
	 */
	if (setup_q->param_valid & (VFPF_RXQ_VALID|VFPF_TXQ_VALID)) {
		struct bnx2x_vf_queue *q = vfq_get(vf, setup_q->vf_qid);
		unsigned long q_type = 0;

		struct bnx2x_queue_init_params *init_p;
		struct bnx2x_queue_setup_params *setup_p;

		if (bnx2x_vfq_is_leading(q))
			bnx2x_leading_vfq_init(bp, vf, q);

		/* re-init the VF operation context */
		memset(&qctor, 0 ,
		       sizeof(struct bnx2x_vf_queue_construct_params));
		setup_p = &qctor.prep_qsetup;
		init_p =  &qctor.qstate.params.init;

		/* activate immediately */
		__set_bit(BNX2X_Q_FLG_ACTIVE, &setup_p->flags);

		if (setup_q->param_valid & VFPF_TXQ_VALID) {
			struct bnx2x_txq_setup_params *txq_params =
				&setup_p->txq_params;

			__set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);

			/* save sb resource index */
			q->sb_idx = setup_q->txq.vf_sb;

			/* tx init */
			init_p->tx.hc_rate = setup_q->txq.hc_rate;
			init_p->tx.sb_cq_index = setup_q->txq.sb_index;

			bnx2x_vf_mbx_set_q_flags(bp, setup_q->txq.flags,
						 &init_p->tx.flags);

			/* tx setup - flags */
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->txq.flags,
						 &setup_p->flags);

			/* tx setup - general, nothing */

			/* tx setup - tx */
			txq_params->dscr_map = setup_q->txq.txq_addr;
			txq_params->sb_cq_index = setup_q->txq.sb_index;
			txq_params->traffic_type = setup_q->txq.traffic_type;

			bnx2x_vfop_qctor_dump_tx(bp, vf, init_p, setup_p,
						 q->index, q->sb_idx);
		}

		if (setup_q->param_valid & VFPF_RXQ_VALID) {
			struct bnx2x_rxq_setup_params *rxq_params =
							&setup_p->rxq_params;

			__set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);

			/* Note: there is no support for different SBs
			 * for TX and RX
			 */
			q->sb_idx = setup_q->rxq.vf_sb;

			/* rx init */
			init_p->rx.hc_rate = setup_q->rxq.hc_rate;
			init_p->rx.sb_cq_index = setup_q->rxq.sb_index;
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->rxq.flags,
						 &init_p->rx.flags);

			/* rx setup - flags */
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->rxq.flags,
						 &setup_p->flags);

			/* rx setup - general */
			setup_p->gen_params.mtu = setup_q->rxq.mtu;

			/* rx setup - rx */
			rxq_params->drop_flags = setup_q->rxq.drop_flags;
			rxq_params->dscr_map = setup_q->rxq.rxq_addr;
			rxq_params->sge_map = setup_q->rxq.sge_addr;
			rxq_params->rcq_map = setup_q->rxq.rcq_addr;
			rxq_params->rcq_np_map = setup_q->rxq.rcq_np_addr;
			rxq_params->buf_sz = setup_q->rxq.buf_sz;
			rxq_params->tpa_agg_sz = setup_q->rxq.tpa_agg_sz;
			rxq_params->max_sges_pkt = setup_q->rxq.max_sge_pkt;
			rxq_params->sge_buf_sz = setup_q->rxq.sge_buf_sz;
			rxq_params->cache_line_log =
				setup_q->rxq.cache_line_log;
			rxq_params->sb_cq_index = setup_q->rxq.sb_index;

			/* rx setup - multicast engine */
			if (bnx2x_vfq_is_leading(q)) {
				u8 mcast_id = FW_VF_HANDLE(vf->abs_vfid);

				rxq_params->mcast_engine_id = mcast_id;
				__set_bit(BNX2X_Q_FLG_MCAST, &setup_p->flags);
			}

			bnx2x_vfop_qctor_dump_rx(bp, vf, init_p, setup_p,
						 q->index, q->sb_idx);
		}
		/* complete the preparations */
		bnx2x_vfop_qctor_prep(bp, vf, q, &qctor, q_type);

		rc = bnx2x_vf_queue_setup(bp, vf, q->index, &qctor);
		if (rc)
			goto response;
	}
response:
	bnx2x_vf_mbx_resp(bp, vf, rc);
}