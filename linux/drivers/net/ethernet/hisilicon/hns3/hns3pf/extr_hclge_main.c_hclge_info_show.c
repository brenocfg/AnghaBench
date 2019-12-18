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
struct hclge_dev {int flag; int /*<<< orphan*/  dv_buf_size; int /*<<< orphan*/  tx_buf_size; int /*<<< orphan*/  pkt_buf_size; int /*<<< orphan*/  hw_tc_map; int /*<<< orphan*/  num_req_vfs; int /*<<< orphan*/  num_vmdq_vport; int /*<<< orphan*/  num_alloc_vport; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  num_tqps; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int HCLGE_FLAG_DCB_ENABLE ; 
 int HCLGE_FLAG_MAIN ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static void hclge_info_show(struct hclge_dev *hdev)
{
	struct device *dev = &hdev->pdev->dev;

	dev_info(dev, "PF info begin:\n");

	dev_info(dev, "Task queue pairs numbers: %d\n", hdev->num_tqps);
	dev_info(dev, "Desc num per TX queue: %d\n", hdev->num_tx_desc);
	dev_info(dev, "Desc num per RX queue: %d\n", hdev->num_rx_desc);
	dev_info(dev, "Numbers of vports: %d\n", hdev->num_alloc_vport);
	dev_info(dev, "Numbers of vmdp vports: %d\n", hdev->num_vmdq_vport);
	dev_info(dev, "Numbers of VF for this PF: %d\n", hdev->num_req_vfs);
	dev_info(dev, "HW tc map: %d\n", hdev->hw_tc_map);
	dev_info(dev, "Total buffer size for TX/RX: %d\n", hdev->pkt_buf_size);
	dev_info(dev, "TX buffer size for each TC: %d\n", hdev->tx_buf_size);
	dev_info(dev, "DV buffer size for each TC: %d\n", hdev->dv_buf_size);
	dev_info(dev, "This is %s PF\n",
		 hdev->flag & HCLGE_FLAG_MAIN ? "main" : "not main");
	dev_info(dev, "DCB %s\n",
		 hdev->flag & HCLGE_FLAG_DCB_ENABLE ? "enable" : "disable");
	dev_info(dev, "MQPRIO %s\n",
		 hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE ? "enable" : "disable");

	dev_info(dev, "PF info end.\n");
}