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
struct TYPE_3__ {struct hns_roce_buf_list tptr_buf; } ;
struct hns_roce_v1_priv {TYPE_1__ tptr_table; } ;
struct hns_roce_dev {int /*<<< orphan*/  tptr_size; int /*<<< orphan*/  tptr_dma_addr; scalar_t__ priv; TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_TPTR_BUF_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_tptr_init(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_buf_list *tptr_buf;
	struct hns_roce_v1_priv *priv;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	tptr_buf = &priv->tptr_table.tptr_buf;

	/*
	 * This buffer will be used for CQ's tptr(tail pointer), also
	 * named ci(customer index). Every CQ will use 2 bytes to save
	 * cqe ci in hip06. Hardware will read this area to get new ci
	 * when the queue is almost full.
	 */
	tptr_buf->buf = dma_alloc_coherent(dev, HNS_ROCE_V1_TPTR_BUF_SIZE,
					   &tptr_buf->map, GFP_KERNEL);
	if (!tptr_buf->buf)
		return -ENOMEM;

	hr_dev->tptr_dma_addr = tptr_buf->map;
	hr_dev->tptr_size = HNS_ROCE_V1_TPTR_BUF_SIZE;

	return 0;
}