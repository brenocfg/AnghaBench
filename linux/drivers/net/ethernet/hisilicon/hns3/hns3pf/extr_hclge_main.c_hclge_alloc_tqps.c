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
struct TYPE_5__ {scalar_t__ io_base; int /*<<< orphan*/  rx_desc_num; int /*<<< orphan*/  tx_desc_num; int /*<<< orphan*/  buf_size; int /*<<< orphan*/ * ae_algo; } ;
struct hclge_tqp {int index; TYPE_2__ q; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {scalar_t__ io_base; } ;
struct hclge_dev {int num_tqps; TYPE_3__ hw; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  rx_buf_len; TYPE_1__* pdev; struct hclge_tqp* htqp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCLGE_TQP_REG_OFFSET ; 
 int HCLGE_TQP_REG_SIZE ; 
 int /*<<< orphan*/  ae_algo ; 
 struct hclge_tqp* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_alloc_tqps(struct hclge_dev *hdev)
{
	struct hclge_tqp *tqp;
	int i;

	hdev->htqp = devm_kcalloc(&hdev->pdev->dev, hdev->num_tqps,
				  sizeof(struct hclge_tqp), GFP_KERNEL);
	if (!hdev->htqp)
		return -ENOMEM;

	tqp = hdev->htqp;

	for (i = 0; i < hdev->num_tqps; i++) {
		tqp->dev = &hdev->pdev->dev;
		tqp->index = i;

		tqp->q.ae_algo = &ae_algo;
		tqp->q.buf_size = hdev->rx_buf_len;
		tqp->q.tx_desc_num = hdev->num_tx_desc;
		tqp->q.rx_desc_num = hdev->num_rx_desc;
		tqp->q.io_base = hdev->hw.io_base + HCLGE_TQP_REG_OFFSET +
			i * HCLGE_TQP_REG_SIZE;

		tqp++;
	}

	return 0;
}