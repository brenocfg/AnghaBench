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
struct ib_udata {int dummy; } ;
struct ib_cq_init_attr {int comp_vector; int cqe; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct hns_roce_ib_create_cq_resp {int /*<<< orphan*/  cqn; } ;
struct TYPE_4__ {int max_cqes; scalar_t__ min_cqes; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  hr_mtt; } ;
struct TYPE_5__ {int cqe; } ;
struct hns_roce_cq {int cq_depth; int /*<<< orphan*/  cqn; int /*<<< orphan*/  event; int /*<<< orphan*/  comp; scalar_t__* tptr_addr; TYPE_3__ hr_buf; int /*<<< orphan*/  lock; TYPE_2__ ib_cq; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EINVAL ; 
 int create_kernel_cq (struct hns_roce_dev*,struct hns_roce_cq*,int) ; 
 int create_user_cq (struct hns_roce_dev*,struct hns_roce_cq*,struct ib_udata*,struct hns_roce_ib_create_cq_resp*,int) ; 
 int /*<<< orphan*/  destroy_kernel_cq (struct hns_roce_dev*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  destroy_user_cq (struct hns_roce_dev*,struct hns_roce_cq*,struct ib_udata*,struct hns_roce_ib_create_cq_resp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int hns_roce_cq_alloc (struct hns_roce_dev*,int,int /*<<< orphan*/ *,struct hns_roce_cq*,int) ; 
 int /*<<< orphan*/  hns_roce_free_cq (struct hns_roce_dev*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_ib_cq_comp ; 
 int /*<<< orphan*/  hns_roce_ib_cq_event ; 
 int ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_create_cq_resp*,int) ; 
 int max (int,scalar_t__) ; 
 int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

int hns_roce_ib_create_cq(struct ib_cq *ib_cq,
			  const struct ib_cq_init_attr *attr,
			  struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_cq->device);
	struct device *dev = hr_dev->dev;
	struct hns_roce_ib_create_cq_resp resp = {};
	struct hns_roce_cq *hr_cq = to_hr_cq(ib_cq);
	int vector = attr->comp_vector;
	int cq_entries = attr->cqe;
	int ret;

	if (cq_entries < 1 || cq_entries > hr_dev->caps.max_cqes) {
		dev_err(dev, "Creat CQ failed. entries=%d, max=%d\n",
			cq_entries, hr_dev->caps.max_cqes);
		return -EINVAL;
	}

	if (hr_dev->caps.min_cqes)
		cq_entries = max(cq_entries, hr_dev->caps.min_cqes);

	cq_entries = roundup_pow_of_two((unsigned int)cq_entries);
	hr_cq->ib_cq.cqe = cq_entries - 1;
	spin_lock_init(&hr_cq->lock);

	if (udata) {
		ret = create_user_cq(hr_dev, hr_cq, udata, &resp, cq_entries);
		if (ret) {
			dev_err(dev, "Create cq failed in user mode!\n");
			goto err_cq;
		}
	} else {
		ret = create_kernel_cq(hr_dev, hr_cq, cq_entries);
		if (ret) {
			dev_err(dev, "Create cq failed in kernel mode!\n");
			goto err_cq;
		}
	}

	/* Allocate cq index, fill cq_context */
	ret = hns_roce_cq_alloc(hr_dev, cq_entries, &hr_cq->hr_buf.hr_mtt,
				hr_cq, vector);
	if (ret) {
		dev_err(dev, "Creat CQ .Failed to cq_alloc.\n");
		goto err_dbmap;
	}

	/*
	 * For the QP created by kernel space, tptr value should be initialized
	 * to zero; For the QP created by user space, it will cause synchronous
	 * problems if tptr is set to zero here, so we initialze it in user
	 * space.
	 */
	if (!udata && hr_cq->tptr_addr)
		*hr_cq->tptr_addr = 0;

	/* Get created cq handler and carry out event */
	hr_cq->comp = hns_roce_ib_cq_comp;
	hr_cq->event = hns_roce_ib_cq_event;
	hr_cq->cq_depth = cq_entries;

	if (udata) {
		resp.cqn = hr_cq->cqn;
		ret = ib_copy_to_udata(udata, &resp, sizeof(resp));
		if (ret)
			goto err_cqc;
	}

	return 0;

err_cqc:
	hns_roce_free_cq(hr_dev, hr_cq);

err_dbmap:
	if (udata)
		destroy_user_cq(hr_dev, hr_cq, udata, &resp);
	else
		destroy_kernel_cq(hr_dev, hr_cq);

err_cq:
	return ret;
}