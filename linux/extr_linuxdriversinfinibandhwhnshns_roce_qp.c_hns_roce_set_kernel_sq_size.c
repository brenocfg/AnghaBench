#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ib_qp_cap {unsigned int max_send_wr; int max_send_sge; scalar_t__ max_inline_data; } ;
struct TYPE_10__ {int wqe_shift; scalar_t__ wqe_cnt; int max_gs; scalar_t__ max_post; scalar_t__ offset; } ;
struct TYPE_9__ {int offset; int wqe_cnt; int wqe_shift; } ;
struct TYPE_8__ {int sge_cnt; int sge_shift; int offset; } ;
struct TYPE_6__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {int sq_max_wqes_per_wr; int buff_size; TYPE_5__ sq; TYPE_4__ rq; TYPE_3__ sge; TYPE_1__ ibqp; scalar_t__ sq_spare_wqes; } ;
struct TYPE_7__ {unsigned int max_wqes; int max_sq_sg; scalar_t__ max_sq_inline; int min_wqes; int mtt_buf_pg_sz; int /*<<< orphan*/  max_sq_desc_sz; } ;
struct hns_roce_dev {TYPE_2__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HNS_ROCE_ALOGN_UP (int,scalar_t__) ; 
 scalar_t__ IB_QPT_GSI ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 scalar_t__ max (unsigned int,int) ; 
 void* roundup_pow_of_two (scalar_t__) ; 

__attribute__((used)) static int hns_roce_set_kernel_sq_size(struct hns_roce_dev *hr_dev,
				       struct ib_qp_cap *cap,
				       struct hns_roce_qp *hr_qp)
{
	struct device *dev = hr_dev->dev;
	u32 page_size;
	u32 max_cnt;
	int size;

	if (cap->max_send_wr  > hr_dev->caps.max_wqes  ||
	    cap->max_send_sge > hr_dev->caps.max_sq_sg ||
	    cap->max_inline_data > hr_dev->caps.max_sq_inline) {
		dev_err(dev, "SQ WR or sge or inline data error!\n");
		return -EINVAL;
	}

	hr_qp->sq.wqe_shift = ilog2(hr_dev->caps.max_sq_desc_sz);
	hr_qp->sq_max_wqes_per_wr = 1;
	hr_qp->sq_spare_wqes = 0;

	if (hr_dev->caps.min_wqes)
		max_cnt = max(cap->max_send_wr, hr_dev->caps.min_wqes);
	else
		max_cnt = cap->max_send_wr;

	hr_qp->sq.wqe_cnt = roundup_pow_of_two(max_cnt);
	if ((u32)hr_qp->sq.wqe_cnt > hr_dev->caps.max_wqes) {
		dev_err(dev, "while setting kernel sq size, sq.wqe_cnt too large\n");
		return -EINVAL;
	}

	/* Get data_seg numbers */
	max_cnt = max(1U, cap->max_send_sge);
	if (hr_dev->caps.max_sq_sg <= 2)
		hr_qp->sq.max_gs = roundup_pow_of_two(max_cnt);
	else
		hr_qp->sq.max_gs = max_cnt;

	if (hr_qp->sq.max_gs > 2) {
		hr_qp->sge.sge_cnt = roundup_pow_of_two(hr_qp->sq.wqe_cnt *
				     (hr_qp->sq.max_gs - 2));
		hr_qp->sge.sge_shift = 4;
	}

	/* ud sqwqe's sge use extend sge */
	if (hr_dev->caps.max_sq_sg > 2 && hr_qp->ibqp.qp_type == IB_QPT_GSI) {
		hr_qp->sge.sge_cnt = roundup_pow_of_two(hr_qp->sq.wqe_cnt *
				     hr_qp->sq.max_gs);
		hr_qp->sge.sge_shift = 4;
	}

	/* Get buf size, SQ and RQ are aligned to PAGE_SIZE */
	page_size = 1 << (hr_dev->caps.mtt_buf_pg_sz + PAGE_SHIFT);
	hr_qp->sq.offset = 0;
	size = HNS_ROCE_ALOGN_UP(hr_qp->sq.wqe_cnt << hr_qp->sq.wqe_shift,
				 page_size);

	if (hr_dev->caps.max_sq_sg > 2 && hr_qp->sge.sge_cnt) {
		hr_qp->sge.offset = size;
		size += HNS_ROCE_ALOGN_UP(hr_qp->sge.sge_cnt <<
					  hr_qp->sge.sge_shift, page_size);
	}

	hr_qp->rq.offset = size;
	size += HNS_ROCE_ALOGN_UP((hr_qp->rq.wqe_cnt << hr_qp->rq.wqe_shift),
				  page_size);
	hr_qp->buff_size = size;

	/* Get wr and sge number which send */
	cap->max_send_wr = hr_qp->sq.max_post = hr_qp->sq.wqe_cnt;
	cap->max_send_sge = hr_qp->sq.max_gs;

	/* We don't support inline sends for kernel QPs (yet) */
	cap->max_inline_data = 0;

	return 0;
}