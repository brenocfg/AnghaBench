#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct hns_roce_idx_que {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  idx_buf; int /*<<< orphan*/  buf_size; } ;
struct hns_roce_srq {struct hns_roce_idx_que idx_que; int /*<<< orphan*/  max; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_roce_buf_alloc (struct hns_roce_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_create_idx_que(struct ib_pd *pd, struct hns_roce_srq *srq,
				   u32 page_shift)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(pd->device);
	struct hns_roce_idx_que *idx_que = &srq->idx_que;

	idx_que->bitmap = bitmap_zalloc(srq->max, GFP_KERNEL);
	if (!idx_que->bitmap)
		return -ENOMEM;

	idx_que->buf_size = srq->idx_que.buf_size;

	if (hns_roce_buf_alloc(hr_dev, idx_que->buf_size, (1 << page_shift) * 2,
			       &idx_que->idx_buf, page_shift)) {
		bitmap_free(idx_que->bitmap);
		return -ENOMEM;
	}

	return 0;
}