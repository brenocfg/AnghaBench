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
struct TYPE_5__ {int flags; } ;
struct hns_roce_dev {TYPE_2__ caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  cqe; } ;
struct TYPE_6__ {int /*<<< orphan*/  hr_mtt; } ;
struct hns_roce_cq {int /*<<< orphan*/  db; TYPE_1__ ib_cq; TYPE_3__ hr_buf; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int /*<<< orphan*/  hns_roce_free_db (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_ib_free_cq_buf (struct hns_roce_dev*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_kernel_cq(struct hns_roce_dev *hr_dev,
			      struct hns_roce_cq *hr_cq)
{
	hns_roce_mtt_cleanup(hr_dev, &hr_cq->hr_buf.hr_mtt);
	hns_roce_ib_free_cq_buf(hr_dev, &hr_cq->hr_buf, hr_cq->ib_cq.cqe);

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB)
		hns_roce_free_db(hr_dev, &hr_cq->db);
}