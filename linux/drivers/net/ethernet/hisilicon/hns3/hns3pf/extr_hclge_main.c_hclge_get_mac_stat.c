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
struct hns3_mac_stats {int /*<<< orphan*/  rx_pause_cnt; int /*<<< orphan*/  tx_pause_cnt; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_rx_mac_pause_num; int /*<<< orphan*/  mac_tx_mac_pause_num; } ;
struct TYPE_4__ {TYPE_1__ mac_stats; } ;
struct hclge_dev {TYPE_2__ hw_stats; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_update_stats (struct hnae3_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_get_mac_stat(struct hnae3_handle *handle,
			       struct hns3_mac_stats *mac_stats)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	hclge_update_stats(handle, NULL);

	mac_stats->tx_pause_cnt = hdev->hw_stats.mac_stats.mac_tx_mac_pause_num;
	mac_stats->rx_pause_cnt = hdev->hw_stats.mac_stats.mac_rx_mac_pause_num;
}