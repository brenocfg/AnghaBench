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
struct TYPE_2__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; } ;
struct hns_roce_srq {int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; TYPE_1__ idx_que; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_user_srq(struct hns_roce_dev *hr_dev,
			     struct hns_roce_srq *srq)
{
	hns_roce_mtt_cleanup(hr_dev, &srq->idx_que.mtt);
	ib_umem_release(srq->idx_que.umem);
	hns_roce_mtt_cleanup(hr_dev, &srq->mtt);
	ib_umem_release(srq->umem);
}