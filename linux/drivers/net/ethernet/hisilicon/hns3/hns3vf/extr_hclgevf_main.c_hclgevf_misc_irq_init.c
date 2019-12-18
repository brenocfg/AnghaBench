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
struct hclgevf_dev {TYPE_2__ misc_vector; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_clear_event_cause (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_enable_vector (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hclgevf_get_misc_vector (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_misc_irq_handle ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_misc_irq_init(struct hclgevf_dev *hdev)
{
	int ret;

	hclgevf_get_misc_vector(hdev);

	ret = request_irq(hdev->misc_vector.vector_irq, hclgevf_misc_irq_handle,
			  0, "hclgevf_cmd", hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev, "VF failed to request misc irq(%d)\n",
			hdev->misc_vector.vector_irq);
		return ret;
	}

	hclgevf_clear_event_cause(hdev, 0);

	/* enable misc. vector(vector 0) */
	hclgevf_enable_vector(&hdev->misc_vector, true);

	return ret;
}