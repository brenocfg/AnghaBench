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
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int /*<<< orphan*/  numa_node_mask; int /*<<< orphan*/ * ae_algo; TYPE_1__* pdev; } ;
struct hclge_vport {struct hclge_dev* back; struct hnae3_handle nic; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  numa_node_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ae_algo ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_knic_setup (struct hclge_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_vport_setup(struct hclge_vport *vport, u16 num_tqps)
{
	struct hnae3_handle *nic = &vport->nic;
	struct hclge_dev *hdev = vport->back;
	int ret;

	nic->pdev = hdev->pdev;
	nic->ae_algo = &ae_algo;
	nic->numa_node_mask = hdev->numa_node_mask;

	ret = hclge_knic_setup(vport, num_tqps,
			       hdev->num_tx_desc, hdev->num_rx_desc);
	if (ret)
		dev_err(&hdev->pdev->dev, "knic setup failed %d\n", ret);

	return ret;
}