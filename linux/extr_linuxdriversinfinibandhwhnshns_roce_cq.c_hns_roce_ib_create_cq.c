#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucmd ;
struct ib_udata {int outlen; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int comp_vector; int cqe; } ;
struct ib_cq {int cqe; } ;
struct hns_roce_uar {int index; } ;
struct hns_roce_ib_create_cq_resp {int /*<<< orphan*/  cqn; int /*<<< orphan*/  cap_flags; } ;
struct hns_roce_ib_create_cq {int /*<<< orphan*/  db_addr; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_12__ {int max_cqes; int flags; scalar_t__ min_cqes; } ;
struct hns_roce_dev {TYPE_1__ caps; scalar_t__ odb_offset; scalar_t__ reg_base; struct hns_roce_uar priv_uar; struct device* dev; } ;
struct TYPE_15__ {scalar_t__* db_record; } ;
struct TYPE_14__ {int /*<<< orphan*/  hr_mtt; } ;
struct hns_roce_cq {int db_en; int cq_depth; TYPE_6__ db; struct ib_cq ib_cq; TYPE_3__ hr_buf; int /*<<< orphan*/  umem; int /*<<< orphan*/  cqn; int /*<<< orphan*/  event; int /*<<< orphan*/  comp; scalar_t__* tptr_addr; scalar_t__ cq_db_l; scalar_t__* set_ci_db; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_13__ {struct hns_roce_uar uar; } ;

/* Variables and functions */
 int DB_REG_OFFSET ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int /*<<< orphan*/  HNS_ROCE_SUPPORT_CQ_RECORD_DB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int hns_roce_alloc_db (struct hns_roce_dev*,TYPE_6__*,int) ; 
 int hns_roce_cq_alloc (struct hns_roce_dev*,int,int /*<<< orphan*/ *,struct hns_roce_uar*,struct hns_roce_cq*,int) ; 
 int hns_roce_db_map_user (TYPE_2__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  hns_roce_db_unmap_user (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  hns_roce_free_cq (struct hns_roce_dev*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_free_db (struct hns_roce_dev*,TYPE_6__*) ; 
 int hns_roce_ib_alloc_cq_buf (struct hns_roce_dev*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  hns_roce_ib_cq_comp ; 
 int /*<<< orphan*/  hns_roce_ib_cq_event ; 
 int /*<<< orphan*/  hns_roce_ib_free_cq_buf (struct hns_roce_dev*,TYPE_3__*,int) ; 
 int hns_roce_ib_get_cq_umem (struct hns_roce_dev*,struct ib_ucontext*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_copy_from_udata (struct hns_roce_ib_create_cq*,struct ib_udata*,int) ; 
 int ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_create_cq_resp*,int) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_cq*) ; 
 struct hns_roce_cq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,scalar_t__) ; 
 int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct hns_roce_dev* to_hr_dev (struct ib_device*) ; 
 TYPE_2__* to_hr_ucontext (struct ib_ucontext*) ; 

struct ib_cq *hns_roce_ib_create_cq(struct ib_device *ib_dev,
				    const struct ib_cq_init_attr *attr,
				    struct ib_ucontext *context,
				    struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_dev);
	struct device *dev = hr_dev->dev;
	struct hns_roce_ib_create_cq ucmd;
	struct hns_roce_ib_create_cq_resp resp = {};
	struct hns_roce_cq *hr_cq = NULL;
	struct hns_roce_uar *uar = NULL;
	int vector = attr->comp_vector;
	int cq_entries = attr->cqe;
	int ret;

	if (cq_entries < 1 || cq_entries > hr_dev->caps.max_cqes) {
		dev_err(dev, "Creat CQ failed. entries=%d, max=%d\n",
			cq_entries, hr_dev->caps.max_cqes);
		return ERR_PTR(-EINVAL);
	}

	hr_cq = kzalloc(sizeof(*hr_cq), GFP_KERNEL);
	if (!hr_cq)
		return ERR_PTR(-ENOMEM);

	if (hr_dev->caps.min_cqes)
		cq_entries = max(cq_entries, hr_dev->caps.min_cqes);

	cq_entries = roundup_pow_of_two((unsigned int)cq_entries);
	hr_cq->ib_cq.cqe = cq_entries - 1;
	spin_lock_init(&hr_cq->lock);

	if (context) {
		if (ib_copy_from_udata(&ucmd, udata, sizeof(ucmd))) {
			dev_err(dev, "Failed to copy_from_udata.\n");
			ret = -EFAULT;
			goto err_cq;
		}

		/* Get user space address, write it into mtt table */
		ret = hns_roce_ib_get_cq_umem(hr_dev, context, &hr_cq->hr_buf,
					      &hr_cq->umem, ucmd.buf_addr,
					      cq_entries);
		if (ret) {
			dev_err(dev, "Failed to get_cq_umem.\n");
			goto err_cq;
		}

		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) &&
		    (udata->outlen >= sizeof(resp))) {
			ret = hns_roce_db_map_user(to_hr_ucontext(context),
						   ucmd.db_addr, &hr_cq->db);
			if (ret) {
				dev_err(dev, "cq record doorbell map failed!\n");
				goto err_mtt;
			}
			hr_cq->db_en = 1;
			resp.cap_flags |= HNS_ROCE_SUPPORT_CQ_RECORD_DB;
		}

		/* Get user space parameters */
		uar = &to_hr_ucontext(context)->uar;
	} else {
		if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) {
			ret = hns_roce_alloc_db(hr_dev, &hr_cq->db, 1);
			if (ret)
				goto err_cq;

			hr_cq->set_ci_db = hr_cq->db.db_record;
			*hr_cq->set_ci_db = 0;
			hr_cq->db_en = 1;
		}

		/* Init mmt table and write buff address to mtt table */
		ret = hns_roce_ib_alloc_cq_buf(hr_dev, &hr_cq->hr_buf,
					       cq_entries);
		if (ret) {
			dev_err(dev, "Failed to alloc_cq_buf.\n");
			goto err_db;
		}

		uar = &hr_dev->priv_uar;
		hr_cq->cq_db_l = hr_dev->reg_base + hr_dev->odb_offset +
				DB_REG_OFFSET * uar->index;
	}

	/* Allocate cq index, fill cq_context */
	ret = hns_roce_cq_alloc(hr_dev, cq_entries, &hr_cq->hr_buf.hr_mtt, uar,
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
	if (!context && hr_cq->tptr_addr)
		*hr_cq->tptr_addr = 0;

	/* Get created cq handler and carry out event */
	hr_cq->comp = hns_roce_ib_cq_comp;
	hr_cq->event = hns_roce_ib_cq_event;
	hr_cq->cq_depth = cq_entries;

	if (context) {
		resp.cqn = hr_cq->cqn;
		ret = ib_copy_to_udata(udata, &resp, sizeof(resp));
		if (ret)
			goto err_cqc;
	}

	return &hr_cq->ib_cq;

err_cqc:
	hns_roce_free_cq(hr_dev, hr_cq);

err_dbmap:
	if (context && (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) &&
	    (udata->outlen >= sizeof(resp)))
		hns_roce_db_unmap_user(to_hr_ucontext(context),
				       &hr_cq->db);

err_mtt:
	hns_roce_mtt_cleanup(hr_dev, &hr_cq->hr_buf.hr_mtt);
	if (context)
		ib_umem_release(hr_cq->umem);
	else
		hns_roce_ib_free_cq_buf(hr_dev, &hr_cq->hr_buf,
					hr_cq->ib_cq.cqe);

err_db:
	if (!context && (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB))
		hns_roce_free_db(hr_dev, &hr_cq->db);

err_cq:
	kfree(hr_cq);
	return ERR_PTR(ret);
}