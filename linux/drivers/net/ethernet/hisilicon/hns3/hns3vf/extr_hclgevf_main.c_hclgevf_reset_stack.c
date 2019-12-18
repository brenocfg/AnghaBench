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
 int /*<<< orphan*/  HNAE3_INIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_RESTORE_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UNINIT_CLIENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_notify_client (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_reset_handshake (struct hclgevf_dev*,int) ; 
 int hclgevf_reset_hdev (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_reset_stack(struct hclgevf_dev *hdev)
{
	int ret;

	/* uninitialize the nic client */
	ret = hclgevf_notify_client(hdev, HNAE3_UNINIT_CLIENT);
	if (ret)
		return ret;

	/* re-initialize the hclge device */
	ret = hclgevf_reset_hdev(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"hclge device re-init failed, VF is disabled!\n");
		return ret;
	}

	/* bring up the nic client again */
	ret = hclgevf_notify_client(hdev, HNAE3_INIT_CLIENT);
	if (ret)
		return ret;

	ret = hclgevf_notify_client(hdev, HNAE3_RESTORE_CLIENT);
	if (ret)
		return ret;

	/* clear handshake status with IMP */
	hclgevf_reset_handshake(hdev, false);

	return 0;
}