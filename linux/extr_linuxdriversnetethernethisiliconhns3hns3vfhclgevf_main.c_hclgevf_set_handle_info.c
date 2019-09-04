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
struct hnae3_handle {int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node_mask; TYPE_2__* pdev; int /*<<< orphan*/ * ae_algo; } ;
struct hclgevf_dev {TYPE_2__* pdev; TYPE_1__* ae_dev; int /*<<< orphan*/  numa_node_mask; struct hnae3_handle nic; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ dev_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNAE3_DEV_KNIC ; 
 int /*<<< orphan*/  HNAE3_SUPPORT_VF ; 
 int /*<<< orphan*/  ae_algovf ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_knic_setup (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_set_handle_info(struct hclgevf_dev *hdev)
{
	struct hnae3_handle *nic = &hdev->nic;
	int ret;

	nic->ae_algo = &ae_algovf;
	nic->pdev = hdev->pdev;
	nic->numa_node_mask = hdev->numa_node_mask;
	nic->flags |= HNAE3_SUPPORT_VF;

	if (hdev->ae_dev->dev_type != HNAE3_DEV_KNIC) {
		dev_err(&hdev->pdev->dev, "unsupported device type %d\n",
			hdev->ae_dev->dev_type);
		return -EINVAL;
	}

	ret = hclgevf_knic_setup(hdev);
	if (ret)
		dev_err(&hdev->pdev->dev, "VF knic setup failed %d\n",
			ret);
	return ret;
}