#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int offset; } ;
struct TYPE_6__ {scalar_t__ sge_cnt; int offset; } ;
struct TYPE_5__ {int offset; } ;
struct hns_roce_qp {int buff_size; TYPE_4__ rq; TYPE_2__ sge; TYPE_1__ sq; } ;
struct TYPE_7__ {int /*<<< orphan*/  wqe_rq_hop_num; int /*<<< orphan*/  wqe_sge_hop_num; int /*<<< orphan*/  wqe_sq_hop_num; } ;
struct hns_roce_dev {TYPE_3__ caps; } ;
struct hns_roce_buf_region {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  hns_roce_init_buf_region (struct hns_roce_buf_region*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int split_wqe_buf_region(struct hns_roce_dev *hr_dev,
				struct hns_roce_qp *hr_qp,
				struct hns_roce_buf_region *regions,
				int region_max, int page_shift)
{
	int page_size = 1 << page_shift;
	bool is_extend_sge;
	int region_cnt = 0;
	int buf_size;
	int buf_cnt;

	if (hr_qp->buff_size < 1 || region_max < 1)
		return region_cnt;

	if (hr_qp->sge.sge_cnt > 0)
		is_extend_sge = true;
	else
		is_extend_sge = false;

	/* sq region */
	if (is_extend_sge)
		buf_size = hr_qp->sge.offset - hr_qp->sq.offset;
	else
		buf_size = hr_qp->rq.offset - hr_qp->sq.offset;

	if (buf_size > 0 && region_cnt < region_max) {
		buf_cnt = DIV_ROUND_UP(buf_size, page_size);
		hns_roce_init_buf_region(&regions[region_cnt],
					 hr_dev->caps.wqe_sq_hop_num,
					 hr_qp->sq.offset / page_size,
					 buf_cnt);
		region_cnt++;
	}

	/* sge region */
	if (is_extend_sge) {
		buf_size = hr_qp->rq.offset - hr_qp->sge.offset;
		if (buf_size > 0 && region_cnt < region_max) {
			buf_cnt = DIV_ROUND_UP(buf_size, page_size);
			hns_roce_init_buf_region(&regions[region_cnt],
						 hr_dev->caps.wqe_sge_hop_num,
						 hr_qp->sge.offset / page_size,
						 buf_cnt);
			region_cnt++;
		}
	}

	/* rq region */
	buf_size = hr_qp->buff_size - hr_qp->rq.offset;
	if (buf_size > 0) {
		buf_cnt = DIV_ROUND_UP(buf_size, page_size);
		hns_roce_init_buf_region(&regions[region_cnt],
					 hr_dev->caps.wqe_rq_hop_num,
					 hr_qp->rq.offset / page_size,
					 buf_cnt);
		region_cnt++;
	}

	return region_cnt;
}