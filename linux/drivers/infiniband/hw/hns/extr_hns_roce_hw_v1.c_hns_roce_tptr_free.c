#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hns_roce_buf_list {int /*<<< orphan*/  map; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {struct hns_roce_buf_list tptr_buf; } ;
struct hns_roce_v1_priv {TYPE_2__ tptr_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_V1_TPTR_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_tptr_free(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_buf_list *tptr_buf;
	struct hns_roce_v1_priv *priv;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	tptr_buf = &priv->tptr_table.tptr_buf;

	dma_free_coherent(dev, HNS_ROCE_V1_TPTR_BUF_SIZE,
			  tptr_buf->buf, tptr_buf->map);
}