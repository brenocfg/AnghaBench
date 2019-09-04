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
struct TYPE_2__ {int /*<<< orphan*/  crq; int /*<<< orphan*/  csq; } ;
struct hns_roce_v2_priv {TYPE_1__ cmq; } ;
struct hns_roce_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_free_cmq_desc (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_v2_cmq_exit(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;

	hns_roce_free_cmq_desc(hr_dev, &priv->cmq.csq);
	hns_roce_free_cmq_desc(hr_dev, &priv->cmq.crq);
}