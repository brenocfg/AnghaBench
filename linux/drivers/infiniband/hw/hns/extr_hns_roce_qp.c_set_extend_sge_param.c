#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int sge_shift; void* sge_cnt; } ;
struct TYPE_7__ {int max_gs; int wqe_cnt; } ;
struct TYPE_6__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {TYPE_5__ sge; TYPE_2__ sq; TYPE_1__ ibqp; } ;
struct TYPE_9__ {int max_sq_sg; void* max_extend_sg; } ;
struct hns_roce_dev {TYPE_4__ caps; TYPE_3__* pci_dev; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_QPT_GSI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,void*) ; 
 void* roundup_pow_of_two (int) ; 

__attribute__((used)) static int set_extend_sge_param(struct hns_roce_dev *hr_dev,
				struct hns_roce_qp *hr_qp)
{
	struct device *dev = hr_dev->dev;

	if (hr_qp->sq.max_gs > 2) {
		hr_qp->sge.sge_cnt = roundup_pow_of_two(hr_qp->sq.wqe_cnt *
				     (hr_qp->sq.max_gs - 2));
		hr_qp->sge.sge_shift = 4;
	}

	/* ud sqwqe's sge use extend sge */
	if (hr_dev->caps.max_sq_sg > 2 && hr_qp->ibqp.qp_type == IB_QPT_GSI) {
		hr_qp->sge.sge_cnt = roundup_pow_of_two(hr_qp->sq.wqe_cnt *
				     hr_qp->sq.max_gs);
		hr_qp->sge.sge_shift = 4;
	}

	if ((hr_qp->sq.max_gs > 2) && hr_dev->pci_dev->revision == 0x20) {
		if (hr_qp->sge.sge_cnt > hr_dev->caps.max_extend_sg) {
			dev_err(dev, "The extended sge cnt error! sge_cnt=%d\n",
				hr_qp->sge.sge_cnt);
			return -EINVAL;
		}
	}

	return 0;
}