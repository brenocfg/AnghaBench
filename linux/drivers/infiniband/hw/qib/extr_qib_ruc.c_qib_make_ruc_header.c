#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {int s_cur_size; int s_hdrwords; scalar_t__ s_mig_state; int remote_qpn; int /*<<< orphan*/  s_pkey_index; int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  port_num; TYPE_1__ ibqp; struct qib_qp_priv* priv; } ;
struct qib_qp_priv {TYPE_4__* s_hdr; } ;
struct qib_ibport {int* sl_to_vl; TYPE_5__* pmastats; } ;
struct ib_other_headers {void** bth; } ;
struct TYPE_12__ {int lid; } ;
struct TYPE_11__ {int /*<<< orphan*/  n_unicast_xmit; } ;
struct TYPE_8__ {int /*<<< orphan*/  grh; } ;
struct TYPE_9__ {TYPE_2__ l; } ;
struct TYPE_10__ {void** lrh; TYPE_3__ u; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_BTH_MIG_REQ ; 
 scalar_t__ IB_MIG_MIGRATED ; 
 int QIB_LRH_BTH ; 
 int QIB_LRH_GRH ; 
 int SIZE_OF_CRC ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 TYPE_6__* ppd_from_ibp (struct qib_ibport*) ; 
 int qib_get_pkey (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 scalar_t__ qib_make_grh (struct qib_ibport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int rdma_ah_get_ah_flags (int /*<<< orphan*/ *) ; 
 int rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 int rdma_ah_get_path_bits (int /*<<< orphan*/ *) ; 
 int rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_read_grh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void qib_make_ruc_header(struct rvt_qp *qp, struct ib_other_headers *ohdr,
			 u32 bth0, u32 bth2)
{
	struct qib_qp_priv *priv = qp->priv;
	struct qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	u16 lrh0;
	u32 nwords;
	u32 extra_bytes;

	/* Construct the header. */
	extra_bytes = -qp->s_cur_size & 3;
	nwords = (qp->s_cur_size + extra_bytes) >> 2;
	lrh0 = QIB_LRH_BTH;
	if (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)) {
		qp->s_hdrwords +=
			qib_make_grh(ibp, &priv->s_hdr->u.l.grh,
				     rdma_ah_read_grh(&qp->remote_ah_attr),
				     qp->s_hdrwords, nwords);
		lrh0 = QIB_LRH_GRH;
	}
	lrh0 |= ibp->sl_to_vl[rdma_ah_get_sl(&qp->remote_ah_attr)] << 12 |
		rdma_ah_get_sl(&qp->remote_ah_attr) << 4;
	priv->s_hdr->lrh[0] = cpu_to_be16(lrh0);
	priv->s_hdr->lrh[1] =
			cpu_to_be16(rdma_ah_get_dlid(&qp->remote_ah_attr));
	priv->s_hdr->lrh[2] =
			cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	priv->s_hdr->lrh[3] =
		cpu_to_be16(ppd_from_ibp(ibp)->lid |
			    rdma_ah_get_path_bits(&qp->remote_ah_attr));
	bth0 |= qib_get_pkey(ibp, qp->s_pkey_index);
	bth0 |= extra_bytes << 20;
	if (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(bth2);
	this_cpu_inc(ibp->pmastats->n_unicast_xmit);
}