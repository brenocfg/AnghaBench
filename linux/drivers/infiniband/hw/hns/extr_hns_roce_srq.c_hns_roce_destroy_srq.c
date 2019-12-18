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
struct ib_srq {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; } ;
struct hns_roce_srq {int max; int wqe_shift; int /*<<< orphan*/  umem; TYPE_1__ idx_que; int /*<<< orphan*/  buf; int /*<<< orphan*/  wrid; int /*<<< orphan*/  mtt; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_srq_free (struct hns_roce_dev*,struct hns_roce_srq*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_srq* to_hr_srq (struct ib_srq*) ; 

void hns_roce_destroy_srq(struct ib_srq *ibsrq, struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	struct hns_roce_srq *srq = to_hr_srq(ibsrq);

	hns_roce_srq_free(hr_dev, srq);
	hns_roce_mtt_cleanup(hr_dev, &srq->mtt);

	if (udata) {
		hns_roce_mtt_cleanup(hr_dev, &srq->idx_que.mtt);
	} else {
		kvfree(srq->wrid);
		hns_roce_buf_free(hr_dev, srq->max << srq->wqe_shift,
				  &srq->buf);
	}
	ib_umem_release(srq->idx_que.umem);
	ib_umem_release(srq->umem);
}