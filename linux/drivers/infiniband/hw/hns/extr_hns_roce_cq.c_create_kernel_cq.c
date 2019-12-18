#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hns_roce_uar {int index; } ;
struct TYPE_4__ {int flags; } ;
struct hns_roce_dev {TYPE_1__ caps; scalar_t__ odb_offset; scalar_t__ reg_base; struct hns_roce_uar priv_uar; struct device* dev; } ;
struct TYPE_5__ {scalar_t__* db_record; } ;
struct hns_roce_cq {int db_en; TYPE_2__ db; scalar_t__ cq_db_l; int /*<<< orphan*/  hr_buf; scalar_t__* set_ci_db; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DB_REG_OFFSET ; 
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_alloc_db (struct hns_roce_dev*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  hns_roce_free_db (struct hns_roce_dev*,TYPE_2__*) ; 
 int hns_roce_ib_alloc_cq_buf (struct hns_roce_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int create_kernel_cq(struct hns_roce_dev *hr_dev,
			    struct hns_roce_cq *hr_cq, int cq_entries)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_uar *uar;
	int ret;

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) {
		ret = hns_roce_alloc_db(hr_dev, &hr_cq->db, 1);
		if (ret)
			return ret;

		hr_cq->set_ci_db = hr_cq->db.db_record;
		*hr_cq->set_ci_db = 0;
		hr_cq->db_en = 1;
	}

	/* Init mtt table and write buff address to mtt table */
	ret = hns_roce_ib_alloc_cq_buf(hr_dev, &hr_cq->hr_buf, cq_entries);
	if (ret) {
		dev_err(dev, "Failed to alloc_cq_buf.\n");
		goto err_db;
	}

	uar = &hr_dev->priv_uar;
	hr_cq->cq_db_l = hr_dev->reg_base + hr_dev->odb_offset +
			 DB_REG_OFFSET * uar->index;

	return 0;

err_db:
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB)
		hns_roce_free_db(hr_dev, &hr_cq->db);

	return ret;
}