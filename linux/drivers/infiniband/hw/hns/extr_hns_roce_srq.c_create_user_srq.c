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
typedef  int /*<<< orphan*/  ucmd ;
typedef  int u32 ;
struct ib_udata {int dummy; } ;
struct TYPE_6__ {int buf_size; void* umem; int /*<<< orphan*/  mtt; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct hns_roce_srq {void* umem; int /*<<< orphan*/  mtt; TYPE_3__ idx_que; TYPE_1__ ibsrq; } ;
struct hns_roce_ib_create_srq {int /*<<< orphan*/  que_addr; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_5__ {int srqwqe_buf_pg_sz; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; TYPE_2__ caps; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hns_roce_ib_umem_write_mtt (struct hns_roce_dev*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_mtt_init (struct hns_roce_dev*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_copy_from_udata (struct hns_roce_ib_create_srq*,struct ib_udata*,int) ; 
 void* ib_umem_get (struct ib_udata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_umem_page_count (void*) ; 
 int /*<<< orphan*/  ib_umem_release (void*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_user_srq(struct hns_roce_srq *srq, struct ib_udata *udata,
			   int srq_buf_size)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(srq->ibsrq.device);
	struct hns_roce_ib_create_srq  ucmd;
	u32 page_shift;
	u32 npages;
	int ret;

	if (ib_copy_from_udata(&ucmd, udata, sizeof(ucmd)))
		return -EFAULT;

	srq->umem = ib_umem_get(udata, ucmd.buf_addr, srq_buf_size, 0, 0);
	if (IS_ERR(srq->umem))
		return PTR_ERR(srq->umem);

	npages = (ib_umem_page_count(srq->umem) +
		(1 << hr_dev->caps.srqwqe_buf_pg_sz) - 1) /
		(1 << hr_dev->caps.srqwqe_buf_pg_sz);
	page_shift = PAGE_SHIFT + hr_dev->caps.srqwqe_buf_pg_sz;
	ret = hns_roce_mtt_init(hr_dev, npages, page_shift, &srq->mtt);
	if (ret)
		goto err_user_buf;

	ret = hns_roce_ib_umem_write_mtt(hr_dev, &srq->mtt, srq->umem);
	if (ret)
		goto err_user_srq_mtt;

	/* config index queue BA */
	srq->idx_que.umem = ib_umem_get(udata, ucmd.que_addr,
					srq->idx_que.buf_size, 0, 0);
	if (IS_ERR(srq->idx_que.umem)) {
		dev_err(hr_dev->dev, "ib_umem_get error for index queue\n");
		ret = PTR_ERR(srq->idx_que.umem);
		goto err_user_srq_mtt;
	}

	ret = hns_roce_mtt_init(hr_dev, ib_umem_page_count(srq->idx_que.umem),
				PAGE_SHIFT, &srq->idx_que.mtt);

	if (ret) {
		dev_err(hr_dev->dev, "hns_roce_mtt_init error for idx que\n");
		goto err_user_idx_mtt;
	}

	ret = hns_roce_ib_umem_write_mtt(hr_dev, &srq->idx_que.mtt,
					 srq->idx_que.umem);
	if (ret) {
		dev_err(hr_dev->dev,
			"hns_roce_ib_umem_write_mtt error for idx que\n");
		goto err_user_idx_buf;
	}

	return 0;

err_user_idx_buf:
	hns_roce_mtt_cleanup(hr_dev, &srq->idx_que.mtt);

err_user_idx_mtt:
	ib_umem_release(srq->idx_que.umem);

err_user_srq_mtt:
	hns_roce_mtt_cleanup(hr_dev, &srq->mtt);

err_user_buf:
	ib_umem_release(srq->umem);

	return ret;
}