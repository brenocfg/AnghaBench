#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  page_shift; int /*<<< orphan*/  npages; } ;
struct TYPE_9__ {int buf_size; int /*<<< orphan*/  bitmap; TYPE_4__ idx_buf; int /*<<< orphan*/  mtt; } ;
struct TYPE_8__ {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct hns_roce_srq {TYPE_4__ buf; int /*<<< orphan*/  mtt; TYPE_3__ idx_que; int /*<<< orphan*/  wrid; scalar_t__ max; TYPE_2__ ibsrq; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_7__ {int srqwqe_buf_pg_sz; int idx_buf_pg_sz; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ hns_roce_buf_alloc (struct hns_roce_dev*,int,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int,TYPE_4__*) ; 
 int hns_roce_buf_write_mtt (struct hns_roce_dev*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int hns_roce_create_idx_que (int /*<<< orphan*/ ,struct hns_roce_srq*,int) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_mtt_init (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_kernel_srq(struct hns_roce_srq *srq, int srq_buf_size)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(srq->ibsrq.device);
	u32 page_shift = PAGE_SHIFT + hr_dev->caps.srqwqe_buf_pg_sz;
	int ret;

	if (hns_roce_buf_alloc(hr_dev, srq_buf_size, (1 << page_shift) * 2,
			       &srq->buf, page_shift))
		return -ENOMEM;

	srq->head = 0;
	srq->tail = srq->max - 1;

	ret = hns_roce_mtt_init(hr_dev, srq->buf.npages, srq->buf.page_shift,
				&srq->mtt);
	if (ret)
		goto err_kernel_buf;

	ret = hns_roce_buf_write_mtt(hr_dev, &srq->mtt, &srq->buf);
	if (ret)
		goto err_kernel_srq_mtt;

	page_shift = PAGE_SHIFT + hr_dev->caps.idx_buf_pg_sz;
	ret = hns_roce_create_idx_que(srq->ibsrq.pd, srq, page_shift);
	if (ret) {
		dev_err(hr_dev->dev, "Create idx queue fail(%d)!\n", ret);
		goto err_kernel_srq_mtt;
	}

	/* Init mtt table for idx_que */
	ret = hns_roce_mtt_init(hr_dev, srq->idx_que.idx_buf.npages,
				srq->idx_que.idx_buf.page_shift,
				&srq->idx_que.mtt);
	if (ret)
		goto err_kernel_create_idx;

	/* Write buffer address into the mtt table */
	ret = hns_roce_buf_write_mtt(hr_dev, &srq->idx_que.mtt,
				     &srq->idx_que.idx_buf);
	if (ret)
		goto err_kernel_idx_buf;

	srq->wrid = kvmalloc_array(srq->max, sizeof(u64), GFP_KERNEL);
	if (!srq->wrid) {
		ret = -ENOMEM;
		goto err_kernel_idx_buf;
	}

	return 0;

err_kernel_idx_buf:
	hns_roce_mtt_cleanup(hr_dev, &srq->idx_que.mtt);

err_kernel_create_idx:
	hns_roce_buf_free(hr_dev, srq->idx_que.buf_size,
			  &srq->idx_que.idx_buf);
	kfree(srq->idx_que.bitmap);

err_kernel_srq_mtt:
	hns_roce_mtt_cleanup(hr_dev, &srq->mtt);

err_kernel_buf:
	hns_roce_buf_free(hr_dev, srq_buf_size, &srq->buf);

	return ret;
}