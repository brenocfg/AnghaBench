#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int /*<<< orphan*/  outlen; } ;
struct TYPE_13__ {int /*<<< orphan*/  cq; } ;
struct TYPE_10__ {scalar_t__ max_wr; scalar_t__ max_sge; } ;
struct ib_srq_init_attr {TYPE_5__ ext; int /*<<< orphan*/  srq_type; TYPE_2__ attr; } ;
struct ib_srq {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct TYPE_16__ {int /*<<< orphan*/  mtt_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtt_type; } ;
struct TYPE_12__ {int entry_sz; int buf_size; TYPE_3__ mtt; } ;
struct hns_roce_srq {int max; int max_gs; int /*<<< orphan*/  srqn; int /*<<< orphan*/  event; TYPE_8__ mtt; scalar_t__ db_reg_l; TYPE_4__ idx_que; int /*<<< orphan*/  wqe_shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct hns_roce_ib_create_srq_resp {int /*<<< orphan*/  srqn; } ;
struct TYPE_9__ {scalar_t__ max_srq_wrs; scalar_t__ max_srq_sges; } ;
struct hns_roce_dev {scalar_t__ reg_base; int /*<<< orphan*/  dev; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_15__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_14__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int HNS_ROCE_IDX_QUE_ENTRY_SZ ; 
 int /*<<< orphan*/  MTT_TYPE_IDX ; 
 int /*<<< orphan*/  MTT_TYPE_SRQWQE ; 
 scalar_t__ SRQ_DB_REG ; 
 int create_kernel_srq (struct hns_roce_srq*,int) ; 
 int create_user_srq (struct hns_roce_srq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  destroy_kernel_srq (struct hns_roce_dev*,struct hns_roce_srq*,int) ; 
 int /*<<< orphan*/  destroy_user_srq (struct hns_roce_dev*,struct hns_roce_srq*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hns_roce_ib_srq_event ; 
 int hns_roce_srq_alloc (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,struct hns_roce_srq*) ; 
 int /*<<< orphan*/  hns_roce_srq_free (struct hns_roce_dev*,struct hns_roce_srq*) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_create_srq_resp*,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_srq_has_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_7__* to_hr_cq (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_6__* to_hr_pd (int /*<<< orphan*/ ) ; 
 struct hns_roce_srq* to_hr_srq (struct ib_srq*) ; 

int hns_roce_create_srq(struct ib_srq *ib_srq,
			struct ib_srq_init_attr *srq_init_attr,
			struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_srq->device);
	struct hns_roce_ib_create_srq_resp resp = {};
	struct hns_roce_srq *srq = to_hr_srq(ib_srq);
	int srq_desc_size;
	int srq_buf_size;
	int ret = 0;
	u32 cqn;

	/* Check the actual SRQ wqe and SRQ sge num */
	if (srq_init_attr->attr.max_wr >= hr_dev->caps.max_srq_wrs ||
	    srq_init_attr->attr.max_sge > hr_dev->caps.max_srq_sges)
		return -EINVAL;

	mutex_init(&srq->mutex);
	spin_lock_init(&srq->lock);

	srq->max = roundup_pow_of_two(srq_init_attr->attr.max_wr + 1);
	srq->max_gs = srq_init_attr->attr.max_sge;

	srq_desc_size = max(16, 16 * srq->max_gs);

	srq->wqe_shift = ilog2(srq_desc_size);

	srq_buf_size = srq->max * srq_desc_size;

	srq->idx_que.entry_sz = HNS_ROCE_IDX_QUE_ENTRY_SZ;
	srq->idx_que.buf_size = srq->max * srq->idx_que.entry_sz;
	srq->mtt.mtt_type = MTT_TYPE_SRQWQE;
	srq->idx_que.mtt.mtt_type = MTT_TYPE_IDX;

	if (udata) {
		ret = create_user_srq(srq, udata, srq_buf_size);
		if (ret) {
			dev_err(hr_dev->dev, "Create user srq failed\n");
			goto err_srq;
		}
	} else {
		ret = create_kernel_srq(srq, srq_buf_size);
		if (ret) {
			dev_err(hr_dev->dev, "Create kernel srq failed\n");
			goto err_srq;
		}
	}

	cqn = ib_srq_has_cq(srq_init_attr->srq_type) ?
	      to_hr_cq(srq_init_attr->ext.cq)->cqn : 0;

	srq->db_reg_l = hr_dev->reg_base + SRQ_DB_REG;

	ret = hns_roce_srq_alloc(hr_dev, to_hr_pd(ib_srq->pd)->pdn, cqn, 0,
				 &srq->mtt, 0, srq);
	if (ret)
		goto err_wrid;

	srq->event = hns_roce_ib_srq_event;
	resp.srqn = srq->srqn;

	if (udata) {
		if (ib_copy_to_udata(udata, &resp,
				     min(udata->outlen, sizeof(resp)))) {
			ret = -EFAULT;
			goto err_srqc_alloc;
		}
	}

	return 0;

err_srqc_alloc:
	hns_roce_srq_free(hr_dev, srq);

err_wrid:
	if (udata)
		destroy_user_srq(hr_dev, srq);
	else
		destroy_kernel_srq(hr_dev, srq, srq_buf_size);

err_srq:
	return ret;
}