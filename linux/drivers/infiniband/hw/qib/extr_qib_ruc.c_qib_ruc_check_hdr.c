#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_15__ {int /*<<< orphan*/  qp_num; } ;
struct rvt_qp {scalar_t__ s_mig_state; scalar_t__ port_num; int /*<<< orphan*/  remote_ah_attr; TYPE_7__ ibqp; int /*<<< orphan*/  s_pkey_index; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  s_alt_pkey_index; } ;
struct TYPE_9__ {int /*<<< orphan*/  gid_prefix; } ;
struct qib_ibport {TYPE_1__ rvp; } ;
struct TYPE_10__ {int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct TYPE_11__ {TYPE_2__ grh; } ;
struct TYPE_12__ {TYPE_3__ l; } ;
struct ib_header {int /*<<< orphan*/ * lrh; TYPE_4__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_14__ {TYPE_5__ global; } ;
struct ib_global_route {TYPE_6__ dgid; int /*<<< orphan*/  sgid_index; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_16__ {scalar_t__ port; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_BTH_MIG_REQ ; 
 scalar_t__ IB_MIG_ARMED ; 
 scalar_t__ IB_MIG_REARM ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sguid (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_bad_pkey (struct qib_ibport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_get_pkey (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_migrate_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  qib_pkey_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_ah_get_ah_flags (int /*<<< orphan*/ *) ; 
 int rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_ah_get_port_num (int /*<<< orphan*/ *) ; 
 struct ib_global_route* rdma_ah_read_grh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qib_ruc_check_hdr(struct qib_ibport *ibp, struct ib_header *hdr,
		      int has_grh, struct rvt_qp *qp, u32 bth0)
{
	__be64 guid;
	unsigned long flags;

	if (qp->s_mig_state == IB_MIG_ARMED && (bth0 & IB_BTH_MIG_REQ)) {
		if (!has_grh) {
			if (rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			    IB_AH_GRH)
				goto err;
		} else {
			const struct ib_global_route *grh;

			if (!(rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			      IB_AH_GRH))
				goto err;
			grh = rdma_ah_read_grh(&qp->alt_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			if (!gid_ok(&hdr->u.l.grh.dgid,
				    ibp->rvp.gid_prefix, guid))
				goto err;
			if (!gid_ok(&hdr->u.l.grh.sgid,
			    grh->dgid.global.subnet_prefix,
			    grh->dgid.global.interface_id))
				goto err;
		}
		if (!qib_pkey_ok((u16)bth0,
				 qib_get_pkey(ibp, qp->s_alt_pkey_index))) {
			qib_bad_pkey(ibp,
				     (u16)bth0,
				     (be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF,
				     0, qp->ibqp.qp_num,
				     hdr->lrh[3], hdr->lrh[1]);
			goto err;
		}
		/* Validate the SLID. See Ch. 9.6.1.5 and 17.2.8 */
		if ((be16_to_cpu(hdr->lrh[3]) !=
		     rdma_ah_get_dlid(&qp->alt_ah_attr)) ||
		    ppd_from_ibp(ibp)->port !=
			    rdma_ah_get_port_num(&qp->alt_ah_attr))
			goto err;
		spin_lock_irqsave(&qp->s_lock, flags);
		qib_migrate_qp(qp);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	} else {
		if (!has_grh) {
			if (rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			    IB_AH_GRH)
				goto err;
		} else {
			const struct ib_global_route *grh;

			if (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			      IB_AH_GRH))
				goto err;
			grh = rdma_ah_read_grh(&qp->remote_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			if (!gid_ok(&hdr->u.l.grh.dgid,
				    ibp->rvp.gid_prefix, guid))
				goto err;
			if (!gid_ok(&hdr->u.l.grh.sgid,
			    grh->dgid.global.subnet_prefix,
			    grh->dgid.global.interface_id))
				goto err;
		}
		if (!qib_pkey_ok((u16)bth0,
				 qib_get_pkey(ibp, qp->s_pkey_index))) {
			qib_bad_pkey(ibp,
				     (u16)bth0,
				     (be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF,
				     0, qp->ibqp.qp_num,
				     hdr->lrh[3], hdr->lrh[1]);
			goto err;
		}
		/* Validate the SLID. See Ch. 9.6.1.5 */
		if (be16_to_cpu(hdr->lrh[3]) !=
		    rdma_ah_get_dlid(&qp->remote_ah_attr) ||
		    ppd_from_ibp(ibp)->port != qp->port_num)
			goto err;
		if (qp->s_mig_state == IB_MIG_REARM &&
		    !(bth0 & IB_BTH_MIG_REQ))
			qp->s_mig_state = IB_MIG_ARMED;
	}

	return 0;

err:
	return 1;
}