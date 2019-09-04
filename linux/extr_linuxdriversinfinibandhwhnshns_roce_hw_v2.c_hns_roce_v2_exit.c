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
struct hns_roce_v2_priv {int /*<<< orphan*/  tsq; int /*<<< orphan*/  tpq; } ;
struct hns_roce_dev {struct hns_roce_v2_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_free_link_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_v2_exit(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = hr_dev->priv;

	hns_roce_free_link_table(hr_dev, &priv->tpq);
	hns_roce_free_link_table(hr_dev, &priv->tsq);
}