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
struct hns_roce_v2_priv {int /*<<< orphan*/  tsq; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; struct hns_roce_v2_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPQ_LINK_TABLE ; 
 int /*<<< orphan*/  TSQ_LINK_TABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hns_roce_free_link_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_init_link_table (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v2_init(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = hr_dev->priv;
	int ret;

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

	return 0;

err_tpq_init_failed:
	hns_roce_free_link_table(hr_dev, &priv->tsq);

	return ret;
}