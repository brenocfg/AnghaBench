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
struct hclge_dev {int /*<<< orphan*/  state; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_SERVICE_INITED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hclge_handle_all_hw_msix_error (struct hclge_dev*,unsigned long*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hclge_handle_hw_msix_error(struct hclge_dev *hdev,
			       unsigned long *reset_requests)
{
	struct device *dev = &hdev->pdev->dev;

	if (!test_bit(HCLGE_STATE_SERVICE_INITED, &hdev->state)) {
		dev_err(dev,
			"Can't handle - MSIx error reported during dev init\n");
		return 0;
	}

	return hclge_handle_all_hw_msix_error(hdev, reset_requests);
}