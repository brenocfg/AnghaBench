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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int wqe_cnt; scalar_t__ offset; } ;
struct hns_roce_qp {scalar_t__ buff_size; int /*<<< orphan*/  qpn; TYPE_1__ rq; } ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int MTT_MIN_COUNT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_wqe_rq_mtt_count(struct hns_roce_dev *hr_dev,
				   struct hns_roce_qp *hr_qp, int mtt_cnt,
				   u32 page_size)
{
	struct device *dev = hr_dev->dev;

	if (hr_qp->rq.wqe_cnt < 1)
		return true;

	if (mtt_cnt < 1) {
		dev_err(dev, "qp(0x%lx) rqwqe buf ba find failed\n",
			hr_qp->qpn);
		return false;
	}

	if (mtt_cnt < MTT_MIN_COUNT &&
		(hr_qp->rq.offset + page_size) < hr_qp->buff_size) {
		dev_err(dev, "qp(0x%lx) next rqwqe buf ba find failed\n",
			hr_qp->qpn);
		return false;
	}

	return true;
}