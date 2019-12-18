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
struct hns_roce_v2_priv {int /*<<< orphan*/  tsq; int /*<<< orphan*/  tpq; } ;
struct TYPE_2__ {int qpc_timer_bt_num; int cqc_timer_bt_num; } ;
struct hns_roce_dev {int /*<<< orphan*/  qpc_timer_table; int /*<<< orphan*/  cqc_timer_table; int /*<<< orphan*/  dev; TYPE_1__ caps; struct hns_roce_v2_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPQ_LINK_TABLE ; 
 int /*<<< orphan*/  TSQ_LINK_TABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hns_roce_free_link_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_init_link_table (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int hns_roce_table_get (struct hns_roce_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hns_roce_v2_init(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = hr_dev->priv;
	int qpc_count, cqc_count;
	int ret, i;

	/* TSQ includes SQ doorbell and ack doorbell */
	ret = hns_roce_init_link_table(hr_dev, TSQ_LINK_TABLE);
	if (ret) {
		dev_err(hr_dev->dev, "TSQ init failed, ret = %d.\n", ret);
		return ret;
	}

	ret = hns_roce_init_link_table(hr_dev, TPQ_LINK_TABLE);
	if (ret) {
		dev_err(hr_dev->dev, "TPQ init failed, ret = %d.\n", ret);
		goto err_tpq_init_failed;
	}

	/* Alloc memory for QPC Timer buffer space chunk */
	for (qpc_count = 0; qpc_count < hr_dev->caps.qpc_timer_bt_num;
	     qpc_count++) {
		ret = hns_roce_table_get(hr_dev, &hr_dev->qpc_timer_table,
					 qpc_count);
		if (ret) {
			dev_err(hr_dev->dev, "QPC Timer get failed\n");
			goto err_qpc_timer_failed;
		}
	}

	/* Alloc memory for CQC Timer buffer space chunk */
	for (cqc_count = 0; cqc_count < hr_dev->caps.cqc_timer_bt_num;
	     cqc_count++) {
		ret = hns_roce_table_get(hr_dev, &hr_dev->cqc_timer_table,
					 cqc_count);
		if (ret) {
			dev_err(hr_dev->dev, "CQC Timer get failed\n");
			goto err_cqc_timer_failed;
		}
	}

	return 0;

err_cqc_timer_failed:
	for (i = 0; i < cqc_count; i++)
		hns_roce_table_put(hr_dev, &hr_dev->cqc_timer_table, i);

err_qpc_timer_failed:
	for (i = 0; i < qpc_count; i++)
		hns_roce_table_put(hr_dev, &hr_dev->qpc_timer_table, i);

	hns_roce_free_link_table(hr_dev, &priv->tpq);

err_tpq_init_failed:
	hns_roce_free_link_table(hr_dev, &priv->tsq);

	return ret;
}