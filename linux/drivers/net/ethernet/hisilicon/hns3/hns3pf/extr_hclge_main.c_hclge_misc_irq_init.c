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
struct TYPE_4__ {int /*<<< orphan*/  vector_irq; } ;
struct hclge_dev {TYPE_2__ misc_vector; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_free_vector (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_get_misc_vector (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_misc_irq_handle ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hclge_dev*) ; 

__attribute__((used)) static int hclge_misc_irq_init(struct hclge_dev *hdev)
{
	int ret;

	hclge_get_misc_vector(hdev);

	/* this would be explicitly freed in the end */
	ret = request_irq(hdev->misc_vector.vector_irq, hclge_misc_irq_handle,
			  0, "hclge_misc", hdev);
	if (ret) {
		hclge_free_vector(hdev, 0);
		dev_err(&hdev->pdev->dev, "request misc irq(%d) fail\n",
			hdev->misc_vector.vector_irq);
	}

	return ret;
}