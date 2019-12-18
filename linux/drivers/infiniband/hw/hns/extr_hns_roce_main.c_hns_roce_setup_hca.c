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
struct TYPE_2__ {int flags; } ;
struct hns_roce_dev {int /*<<< orphan*/  priv_uar; TYPE_1__ caps; int /*<<< orphan*/  pgdir_mutex; int /*<<< orphan*/  pgdir_list; int /*<<< orphan*/  bt_cmd_lock; int /*<<< orphan*/  sm_lock; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int HNS_ROCE_CAP_FLAG_SRQ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_cq_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_mr_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_pd_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_qp_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_uar_table (struct hns_roce_dev*) ; 
 int hns_roce_init_cq_table (struct hns_roce_dev*) ; 
 int hns_roce_init_mr_table (struct hns_roce_dev*) ; 
 int hns_roce_init_pd_table (struct hns_roce_dev*) ; 
 int hns_roce_init_qp_table (struct hns_roce_dev*) ; 
 int hns_roce_init_srq_table (struct hns_roce_dev*) ; 
 int hns_roce_init_uar_table (struct hns_roce_dev*) ; 
 int hns_roce_uar_alloc (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_uar_free (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_setup_hca(struct hns_roce_dev *hr_dev)
{
	int ret;
	struct device *dev = hr_dev->dev;

	spin_lock_init(&hr_dev->sm_lock);
	spin_lock_init(&hr_dev->bt_cmd_lock);

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) {
		INIT_LIST_HEAD(&hr_dev->pgdir_list);
		mutex_init(&hr_dev->pgdir_mutex);
	}

	ret = hns_roce_init_uar_table(hr_dev);
	if (ret) {
		dev_err(dev, "Failed to initialize uar table. aborting\n");
		return ret;
	}

	ret = hns_roce_uar_alloc(hr_dev, &hr_dev->priv_uar);
	if (ret) {
		dev_err(dev, "Failed to allocate priv_uar.\n");
		goto err_uar_table_free;
	}

	ret = hns_roce_init_pd_table(hr_dev);
	if (ret) {
		dev_err(dev, "Failed to init protected domain table.\n");
		goto err_uar_alloc_free;
	}

	ret = hns_roce_init_mr_table(hr_dev);
	if (ret) {
		dev_err(dev, "Failed to init memory region table.\n");
		goto err_pd_table_free;
	}

	ret = hns_roce_init_cq_table(hr_dev);
	if (ret) {
		dev_err(dev, "Failed to init completion queue table.\n");
		goto err_mr_table_free;
	}

	ret = hns_roce_init_qp_table(hr_dev);
	if (ret) {
		dev_err(dev, "Failed to init queue pair table.\n");
		goto err_cq_table_free;
	}

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) {
		ret = hns_roce_init_srq_table(hr_dev);
		if (ret) {
			dev_err(dev,
				"Failed to init share receive queue table.\n");
			goto err_qp_table_free;
		}
	}

	return 0;

err_qp_table_free:
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ)
		hns_roce_cleanup_qp_table(hr_dev);

err_cq_table_free:
	hns_roce_cleanup_cq_table(hr_dev);

err_mr_table_free:
	hns_roce_cleanup_mr_table(hr_dev);

err_pd_table_free:
	hns_roce_cleanup_pd_table(hr_dev);

err_uar_alloc_free:
	hns_roce_uar_free(hr_dev, &hr_dev->priv_uar);

err_uar_table_free:
	hns_roce_cleanup_uar_table(hr_dev);
	return ret;
}