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
struct TYPE_5__ {int /*<<< orphan*/  orq_size; int /*<<< orphan*/  irq_size; int /*<<< orphan*/  rq_max_sges; int /*<<< orphan*/  rq_size; int /*<<< orphan*/  sq_max_sges; int /*<<< orphan*/  sq_size; } ;
struct siw_qp {TYPE_2__ attrs; } ;
struct siw_device {TYPE_1__* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_inline_data; } ;
struct ib_qp_init_attr {TYPE_3__ cap; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; } ;
struct ib_qp_attr {int qp_access_flags; TYPE_3__ cap; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  path_mtu; } ;
struct ib_qp {int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  SIW_MAX_INLINE ; 
 int /*<<< orphan*/  ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 
 struct siw_qp* to_siw_qp (struct ib_qp*) ; 

int siw_query_qp(struct ib_qp *base_qp, struct ib_qp_attr *qp_attr,
		 int qp_attr_mask, struct ib_qp_init_attr *qp_init_attr)
{
	struct siw_qp *qp;
	struct siw_device *sdev;

	if (base_qp && qp_attr && qp_init_attr) {
		qp = to_siw_qp(base_qp);
		sdev = to_siw_dev(base_qp->device);
	} else {
		return -EINVAL;
	}
	qp_attr->cap.max_inline_data = SIW_MAX_INLINE;
	qp_attr->cap.max_send_wr = qp->attrs.sq_size;
	qp_attr->cap.max_send_sge = qp->attrs.sq_max_sges;
	qp_attr->cap.max_recv_wr = qp->attrs.rq_size;
	qp_attr->cap.max_recv_sge = qp->attrs.rq_max_sges;
	qp_attr->path_mtu = ib_mtu_int_to_enum(sdev->netdev->mtu);
	qp_attr->max_rd_atomic = qp->attrs.irq_size;
	qp_attr->max_dest_rd_atomic = qp->attrs.orq_size;

	qp_attr->qp_access_flags = IB_ACCESS_LOCAL_WRITE |
				   IB_ACCESS_REMOTE_WRITE |
				   IB_ACCESS_REMOTE_READ;

	qp_init_attr->qp_type = base_qp->qp_type;
	qp_init_attr->send_cq = base_qp->send_cq;
	qp_init_attr->recv_cq = base_qp->recv_cq;
	qp_init_attr->srq = base_qp->srq;

	qp_init_attr->cap = qp_attr->cap;

	return 0;
}