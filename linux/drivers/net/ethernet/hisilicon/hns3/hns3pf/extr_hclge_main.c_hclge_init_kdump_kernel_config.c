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
struct hclge_dev {int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; scalar_t__ num_req_vfs; scalar_t__ num_vmdq_vport; scalar_t__ num_tqps; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MIN_RX_DESC ; 
 int /*<<< orphan*/  HCLGE_MIN_TX_DESC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_kdump_kernel () ; 

__attribute__((used)) static void hclge_init_kdump_kernel_config(struct hclge_dev *hdev)
{
#define HCLGE_MIN_TX_DESC	64
#define HCLGE_MIN_RX_DESC	64

	if (!is_kdump_kernel())
		return;

	dev_info(&hdev->pdev->dev,
		 "Running kdump kernel. Using minimal resources\n");

	/* minimal queue pairs equals to the number of vports */
	hdev->num_tqps = hdev->num_vmdq_vport + hdev->num_req_vfs + 1;
	hdev->num_tx_desc = HCLGE_MIN_TX_DESC;
	hdev->num_rx_desc = HCLGE_MIN_RX_DESC;
}