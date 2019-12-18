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
struct verbs_txreq {int s_cur_size; int /*<<< orphan*/  txreq; } ;
struct TYPE_2__ {int qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {int /*<<< orphan*/  pmtu; TYPE_1__ ibqp; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int s_running_pkt_size; int /*<<< orphan*/  s_iowait; } ;
struct hfi1_pkt_state {int opcode; struct verbs_txreq* s_txreq; } ;
struct hfi1_devdata {int flags; int /*<<< orphan*/  process_dma_send; int /*<<< orphan*/  process_pio_send; } ;
typedef  int /*<<< orphan*/  send_routine ;

/* Variables and functions */
 int BIT (int) ; 
 int HFI1_HAS_SEND_DMA ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int OPMASK ; 
 struct hfi1_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowait_sdma_pending (int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pio_opmask ; 
 int /*<<< orphan*/  piothreshold ; 
 int /*<<< orphan*/  sdma_txreq_built (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline send_routine get_send_routine(struct rvt_qp *qp,
					    struct hfi1_pkt_state *ps)
{
	struct hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	struct hfi1_qp_priv *priv = qp->priv;
	struct verbs_txreq *tx = ps->s_txreq;

	if (unlikely(!(dd->flags & HFI1_HAS_SEND_DMA)))
		return dd->process_pio_send;
	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		return dd->process_pio_send;
	case IB_QPT_GSI:
	case IB_QPT_UD:
		break;
	case IB_QPT_UC:
	case IB_QPT_RC:
		priv->s_running_pkt_size =
			(tx->s_cur_size + priv->s_running_pkt_size) / 2;
		if (piothreshold &&
		    priv->s_running_pkt_size <= min(piothreshold, qp->pmtu) &&
		    (BIT(ps->opcode & OPMASK) & pio_opmask[ps->opcode >> 5]) &&
		    iowait_sdma_pending(&priv->s_iowait) == 0 &&
		    !sdma_txreq_built(&tx->txreq))
			return dd->process_pio_send;
		break;
	default:
		break;
	}
	return dd->process_dma_send;
}