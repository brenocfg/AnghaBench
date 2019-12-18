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
struct TYPE_2__ {int buf_size; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  idx_buf; int /*<<< orphan*/  mtt; } ;
struct hns_roce_srq {int /*<<< orphan*/  buf; int /*<<< orphan*/  mtt; TYPE_1__ idx_que; int /*<<< orphan*/  wrid; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_kernel_srq(struct hns_roce_dev *hr_dev,
			       struct hns_roce_srq *srq, int srq_buf_size)
{
	kvfree(srq->wrid);
	hns_roce_mtt_cleanup(hr_dev, &srq->idx_que.mtt);
	hns_roce_buf_free(hr_dev, srq->idx_que.buf_size, &srq->idx_que.idx_buf);
	kfree(srq->idx_que.bitmap);
	hns_roce_mtt_cleanup(hr_dev, &srq->mtt);
	hns_roce_buf_free(hr_dev, srq_buf_size, &srq->buf);
}