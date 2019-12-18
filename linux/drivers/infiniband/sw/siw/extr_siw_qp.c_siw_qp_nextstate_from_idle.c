#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct siw_qp_attrs {int state; int flags; int /*<<< orphan*/  sk; int /*<<< orphan*/  orq_size; int /*<<< orphan*/  irq_size; } ;
struct TYPE_6__ {int state; int /*<<< orphan*/  irq_size; int /*<<< orphan*/  orq_size; int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {int* ddp_msn; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ddp_msn; } ;
struct siw_qp {int /*<<< orphan*/ * cep; TYPE_3__ attrs; TYPE_2__ rx_stream; TYPE_1__ tx_ctx; } ;
typedef  enum siw_qp_attr_mask { ____Placeholder_siw_qp_attr_mask } siw_qp_attr_mask ;

/* Variables and functions */
 int EINVAL ; 
 size_t RDMAP_UNTAGGED_QN_RDMA_READ ; 
 size_t RDMAP_UNTAGGED_QN_SEND ; 
 size_t RDMAP_UNTAGGED_QN_TERMINATE ; 
 int SIW_MPA_CRC ; 
 int SIW_QP_ATTR_LLP_HANDLE ; 
 int SIW_QP_ATTR_MPA ; 
#define  SIW_QP_STATE_ERROR 129 
#define  SIW_QP_STATE_RTS 128 
 int /*<<< orphan*/  siw_cep_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,...) ; 
 int siw_qp_enable_crc (struct siw_qp*) ; 
 int siw_qp_readq_init (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_rq_flush (struct siw_qp*) ; 

__attribute__((used)) static int siw_qp_nextstate_from_idle(struct siw_qp *qp,
				      struct siw_qp_attrs *attrs,
				      enum siw_qp_attr_mask mask)
{
	int rv = 0;

	switch (attrs->state) {
	case SIW_QP_STATE_RTS:
		if (attrs->flags & SIW_MPA_CRC) {
			rv = siw_qp_enable_crc(qp);
			if (rv)
				break;
		}
		if (!(mask & SIW_QP_ATTR_LLP_HANDLE)) {
			siw_dbg_qp(qp, "no socket\n");
			rv = -EINVAL;
			break;
		}
		if (!(mask & SIW_QP_ATTR_MPA)) {
			siw_dbg_qp(qp, "no MPA\n");
			rv = -EINVAL;
			break;
		}
		/*
		 * Initialize iWARP TX state
		 */
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_SEND] = 0;
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ] = 0;
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_TERMINATE] = 0;

		/*
		 * Initialize iWARP RX state
		 */
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_SEND] = 1;
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ] = 1;
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_TERMINATE] = 1;

		/*
		 * init IRD free queue, caller has already checked
		 * limits.
		 */
		rv = siw_qp_readq_init(qp, attrs->irq_size,
				       attrs->orq_size);
		if (rv)
			break;

		qp->attrs.sk = attrs->sk;
		qp->attrs.state = SIW_QP_STATE_RTS;

		siw_dbg_qp(qp, "enter RTS: crc=%s, ord=%u, ird=%u\n",
			   attrs->flags & SIW_MPA_CRC ? "y" : "n",
			   qp->attrs.orq_size, qp->attrs.irq_size);
		break;

	case SIW_QP_STATE_ERROR:
		siw_rq_flush(qp);
		qp->attrs.state = SIW_QP_STATE_ERROR;
		if (qp->cep) {
			siw_cep_put(qp->cep);
			qp->cep = NULL;
		}
		break;

	default:
		break;
	}
	return rv;
}