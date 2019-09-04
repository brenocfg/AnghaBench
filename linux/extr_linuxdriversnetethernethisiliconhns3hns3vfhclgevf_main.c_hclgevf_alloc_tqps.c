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
struct TYPE_5__ {scalar_t__ io_base; int /*<<< orphan*/  desc_num; int /*<<< orphan*/  buf_size; int /*<<< orphan*/ * ae_algo; } ;
struct hclgevf_tqp {int index; TYPE_2__ q; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {scalar_t__ io_base; } ;
struct hclgevf_dev {int num_tqps; TYPE_3__ hw; int /*<<< orphan*/  num_desc; int /*<<< orphan*/  rx_buf_len; TYPE_1__* pdev; struct hclgevf_tqp* htqp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCLGEVF_TQP_REG_OFFSET ; 
 int HCLGEVF_TQP_REG_SIZE ; 
 int /*<<< orphan*/  ae_algovf ; 
 struct hclgevf_tqp* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct hclgevf_tqp*) ; 
 scalar_t__ hclgevf_dev_ongoing_reset (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_alloc_tqps(struct hclgevf_dev *hdev)
{
	struct hclgevf_tqp *tqp;
	int i;

	/* if this is on going reset then we need to re-allocate the TPQs
	 * since we cannot assume we would get same number of TPQs back from PF
	 */
	if (hclgevf_dev_ongoing_reset(hdev))
		devm_kfree(&hdev->pdev->dev, hdev->htqp);

	hdev->htqp = devm_kcalloc(&hdev->pdev->dev, hdev->num_tqps,
				  sizeof(struct hclgevf_tqp), GFP_KERNEL);
	if (!hdev->htqp)
		return -ENOMEM;

	tqp = hdev->htqp;

	for (i = 0; i < hdev->num_tqps; i++) {
		tqp->dev = &hdev->pdev->dev;
		tqp->index = i;

		tqp->q.ae_algo = &ae_algovf;
		tqp->q.buf_size = hdev->rx_buf_len;
		tqp->q.desc_num = hdev->num_desc;
		tqp->q.io_base = hdev->hw.io_base + HCLGEVF_TQP_REG_OFFSET +
			i * HCLGEVF_TQP_REG_SIZE;

		tqp++;
	}

	return 0;
}