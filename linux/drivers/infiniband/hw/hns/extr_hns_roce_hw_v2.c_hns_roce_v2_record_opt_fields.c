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
struct ib_qp_attr {size_t port_num; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  qp_access_flags; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct hns_roce_qp {size_t port; int /*<<< orphan*/  phy_port; int /*<<< orphan*/  resp_depth; int /*<<< orphan*/  atomic_rd_en; } ;
struct TYPE_2__ {int /*<<< orphan*/ * phy_port; } ;
struct hns_roce_dev {TYPE_1__ iboe; } ;

/* Variables and functions */
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_PORT ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static void hns_roce_v2_record_opt_fields(struct ib_qp *ibqp,
					  const struct ib_qp_attr *attr,
					  int attr_mask)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	if (attr_mask & IB_QP_ACCESS_FLAGS)
		hr_qp->atomic_rd_en = attr->qp_access_flags;

	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		hr_qp->resp_depth = attr->max_dest_rd_atomic;
	if (attr_mask & IB_QP_PORT) {
		hr_qp->port = attr->port_num - 1;
		hr_qp->phy_port = hr_dev->iboe.phy_port[hr_qp->port];
	}
}