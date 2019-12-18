#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_12__ {int /*<<< orphan*/  qp_num; } ;
struct rvt_qp {scalar_t__ s_mig_state; scalar_t__ port_num; int /*<<< orphan*/  remote_ah_attr; TYPE_5__ ibqp; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  alt_ah_attr; } ;
struct TYPE_10__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_11__ {TYPE_3__ global; } ;
struct ib_global_route {TYPE_4__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct hfi1_packet {scalar_t__ dlid; scalar_t__ slid; scalar_t__ sl; int migrated; scalar_t__ etype; TYPE_2__* grh; int /*<<< orphan*/  pkey; struct rvt_qp* qp; } ;
struct TYPE_8__ {int /*<<< orphan*/  gid_prefix; } ;
struct hfi1_ibport {TYPE_1__ rvp; int /*<<< orphan*/ * sl_to_sc; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_13__ {scalar_t__ port; } ;
struct TYPE_9__ {int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 scalar_t__ IB_MIG_ARMED ; 
 scalar_t__ IB_MIG_REARM ; 
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 int /*<<< orphan*/  get_sguid (struct hfi1_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_bad_pkey (struct hfi1_ibport*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_migrate_qp (struct rvt_qp*) ; 
 TYPE_6__* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rcv_pkey_check (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rdma_ah_get_ah_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_ah_get_port_num (int /*<<< orphan*/ *) ; 
 size_t rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct ib_global_route* rdma_ah_read_grh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int hfi1_ruc_check_hdr(struct hfi1_ibport *ibp, struct hfi1_packet *packet)
{
	__be64 guid;
	unsigned long flags;
	struct rvt_qp *qp = packet->qp;
	u8 sc5 = ibp->sl_to_sc[rdma_ah_get_sl(&qp->remote_ah_attr)];
	u32 dlid = packet->dlid;
	u32 slid = packet->slid;
	u32 sl = packet->sl;
	bool migrated = packet->migrated;
	u16 pkey = packet->pkey;

	if (qp->s_mig_state == IB_MIG_ARMED && migrated) {
		if (!packet->grh) {
			if ((rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			     IB_AH_GRH) &&
			    (packet->etype != RHF_RCV_TYPE_BYPASS))
				return 1;
		} else {
			const struct ib_global_route *grh;

			if (!(rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			      IB_AH_GRH))
				return 1;
			grh = rdma_ah_read_grh(&qp->alt_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			if (!gid_ok(&packet->grh->dgid, ibp->rvp.gid_prefix,
				    guid))
				return 1;
			if (!gid_ok(
				&packet->grh->sgid,
				grh->dgid.global.subnet_prefix,
				grh->dgid.global.interface_id))
				return 1;
		}
		if (unlikely(rcv_pkey_check(ppd_from_ibp(ibp), pkey,
					    sc5, slid))) {
			hfi1_bad_pkey(ibp, pkey, sl, 0, qp->ibqp.qp_num,
				      slid, dlid);
			return 1;
		}
		/* Validate the SLID. See Ch. 9.6.1.5 and 17.2.8 */
		if (slid != rdma_ah_get_dlid(&qp->alt_ah_attr) ||
		    ppd_from_ibp(ibp)->port !=
			rdma_ah_get_port_num(&qp->alt_ah_attr))
			return 1;
		spin_lock_irqsave(&qp->s_lock, flags);
		hfi1_migrate_qp(qp);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	} else {
		if (!packet->grh) {
			if ((rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			     IB_AH_GRH) &&
			    (packet->etype != RHF_RCV_TYPE_BYPASS))
				return 1;
		} else {
			const struct ib_global_route *grh;

			if (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
						   IB_AH_GRH))
				return 1;
			grh = rdma_ah_read_grh(&qp->remote_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			if (!gid_ok(&packet->grh->dgid, ibp->rvp.gid_prefix,
				    guid))
				return 1;
			if (!gid_ok(
			     &packet->grh->sgid,
			     grh->dgid.global.subnet_prefix,
			     grh->dgid.global.interface_id))
				return 1;
		}
		if (unlikely(rcv_pkey_check(ppd_from_ibp(ibp), pkey,
					    sc5, slid))) {
			hfi1_bad_pkey(ibp, pkey, sl, 0, qp->ibqp.qp_num,
				      slid, dlid);
			return 1;
		}
		/* Validate the SLID. See Ch. 9.6.1.5 */
		if ((slid != rdma_ah_get_dlid(&qp->remote_ah_attr)) ||
		    ppd_from_ibp(ibp)->port != qp->port_num)
			return 1;
		if (qp->s_mig_state == IB_MIG_REARM && !migrated)
			qp->s_mig_state = IB_MIG_ARMED;
	}

	return 0;
}