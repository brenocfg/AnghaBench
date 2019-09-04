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
struct hclgevf_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UNINIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hclgevf_notify_client (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int hclgevf_reset_stack (struct hclgevf_dev*) ; 
 int hclgevf_reset_wait (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int hclgevf_reset(struct hclgevf_dev *hdev)
{
	int ret;

	rtnl_lock();

	/* bring down the nic to stop any ongoing TX/RX */
	hclgevf_notify_client(hdev, HNAE3_DOWN_CLIENT);

	rtnl_unlock();

	/* check if VF could successfully fetch the hardware reset completion
	 * status from the hardware
	 */
	ret = hclgevf_reset_wait(hdev);
	if (ret) {
		/* can't do much in this situation, will disable VF */
		dev_err(&hdev->pdev->dev,
			"VF failed(=%d) to fetch H/W reset completion status\n",
			ret);

		dev_warn(&hdev->pdev->dev, "VF reset failed, disabling VF!\n");
		rtnl_lock();
		hclgevf_notify_client(hdev, HNAE3_UNINIT_CLIENT);

		rtnl_unlock();
		return ret;
	}

	rtnl_lock();

	/* now, re-initialize the nic client and ae device*/
	ret = hclgevf_reset_stack(hdev);
	if (ret)
		dev_err(&hdev->pdev->dev, "failed to reset VF stack\n");

	/* bring up the nic to enable TX/RX again */
	hclgevf_notify_client(hdev, HNAE3_UP_CLIENT);

	rtnl_unlock();

	return ret;
}