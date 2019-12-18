#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_send_wr {unsigned long long wr_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * sg_list; scalar_t__ send_flags; scalar_t__ num_sge; int /*<<< orphan*/ * next; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct hns_roce_qp {TYPE_2__ ibqp; } ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  send_wr ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hns_roce_v1_post_send (TYPE_2__*,struct ib_send_wr*,struct ib_send_wr const**) ; 
 int /*<<< orphan*/  memset (struct ib_send_wr*,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v1_send_lp_wqe(struct hns_roce_qp *hr_qp)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(hr_qp->ibqp.device);
	struct device *dev = &hr_dev->pdev->dev;
	struct ib_send_wr send_wr;
	const struct ib_send_wr *bad_wr;
	int ret;

	memset(&send_wr, 0, sizeof(send_wr));
	send_wr.next	= NULL;
	send_wr.num_sge	= 0;
	send_wr.send_flags = 0;
	send_wr.sg_list	= NULL;
	send_wr.wr_id	= (unsigned long long)&send_wr;
	send_wr.opcode	= IB_WR_RDMA_WRITE;

	ret = hns_roce_v1_post_send(&hr_qp->ibqp, &send_wr, &bad_wr);
	if (ret) {
		dev_err(dev, "Post write wqe for mr free failed(%d)!", ret);
		return ret;
	}

	return 0;
}