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
struct hnae3_ae_dev {int /*<<< orphan*/  reset_type; } ;
struct TYPE_3__ {scalar_t__ rst_fail_cnt; int /*<<< orphan*/  rst_done_cnt; int /*<<< orphan*/  hw_rst_done_cnt; int /*<<< orphan*/  rst_cnt; } ;
struct hclgevf_dev {TYPE_1__ rst_stats; int /*<<< orphan*/  last_reset_time; TYPE_2__* pdev; int /*<<< orphan*/  reset_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 int /*<<< orphan*/  HNAE3_NONE_RESET ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hclgevf_notify_client (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_reset_err_handle (struct hclgevf_dev*) ; 
 int hclgevf_reset_prepare_wait (struct hclgevf_dev*) ; 
 int hclgevf_reset_stack (struct hclgevf_dev*) ; 
 int hclgevf_reset_wait (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct hnae3_ae_dev* pci_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int hclgevf_reset(struct hclgevf_dev *hdev)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	int ret;

	/* Initialize ae_dev reset status as well, in case enet layer wants to
	 * know if device is undergoing reset
	 */
	ae_dev->reset_type = hdev->reset_type;
	hdev->rst_stats.rst_cnt++;
	rtnl_lock();

	/* bring down the nic to stop any ongoing TX/RX */
	ret = hclgevf_notify_client(hdev, HNAE3_DOWN_CLIENT);
	if (ret)
		goto err_reset_lock;

	rtnl_unlock();

	ret = hclgevf_reset_prepare_wait(hdev);
	if (ret)
		goto err_reset;

	/* check if VF could successfully fetch the hardware reset completion
	 * status from the hardware
	 */
	ret = hclgevf_reset_wait(hdev);
	if (ret) {
		/* can't do much in this situation, will disable VF */
		dev_err(&hdev->pdev->dev,
			"VF failed(=%d) to fetch H/W reset completion status\n",
			ret);
		goto err_reset;
	}

	hdev->rst_stats.hw_rst_done_cnt++;

	rtnl_lock();

	/* now, re-initialize the nic client and ae device */
	ret = hclgevf_reset_stack(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev, "failed to reset VF stack\n");
		goto err_reset_lock;
	}

	/* bring up the nic to enable TX/RX again */
	ret = hclgevf_notify_client(hdev, HNAE3_UP_CLIENT);
	if (ret)
		goto err_reset_lock;

	rtnl_unlock();

	hdev->last_reset_time = jiffies;
	ae_dev->reset_type = HNAE3_NONE_RESET;
	hdev->rst_stats.rst_done_cnt++;
	hdev->rst_stats.rst_fail_cnt = 0;

	return ret;
err_reset_lock:
	rtnl_unlock();
err_reset:
	hclgevf_reset_err_handle(hdev);

	return ret;
}