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
struct ib_udata {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {TYPE_1__ ibqp; int /*<<< orphan*/  qpn; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 int hns_roce_v2_destroy_qp_common (struct hns_roce_dev*,struct hns_roce_qp*,struct ib_udata*) ; 
 struct hns_roce_qp* hr_to_hr_sqp (struct hns_roce_qp*) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_qp*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_v2_destroy_qp(struct ib_qp *ibqp, struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	int ret;

	ret = hns_roce_v2_destroy_qp_common(hr_dev, hr_qp, udata);
	if (ret) {
		ibdev_err(&hr_dev->ib_dev, "Destroy qp 0x%06lx failed(%d)\n",
			  hr_qp->qpn, ret);
		return ret;
	}

	if (hr_qp->ibqp.qp_type == IB_QPT_GSI)
		kfree(hr_to_hr_sqp(hr_qp));
	else
		kfree(hr_qp);

	return 0;
}