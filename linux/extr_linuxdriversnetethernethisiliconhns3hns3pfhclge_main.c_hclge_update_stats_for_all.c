#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* netdev; } ;
struct hnae3_handle {TYPE_4__ kinfo; scalar_t__ client; } ;
struct hclge_dev {int /*<<< orphan*/  hw_stats; TYPE_2__* pdev; TYPE_1__* vport; } ;
struct TYPE_7__ {int /*<<< orphan*/  stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_32_bit_update_stats (struct hclge_dev*) ; 
 int hclge_mac_update_stats (struct hclge_dev*) ; 
 int hclge_tqps_update_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_update_netstat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_update_stats_for_all(struct hclge_dev *hdev)
{
	struct hnae3_handle *handle;
	int status;

	handle = &hdev->vport[0].nic;
	if (handle->client) {
		status = hclge_tqps_update_stats(handle);
		if (status) {
			dev_err(&hdev->pdev->dev,
				"Update TQPS stats fail, status = %d.\n",
				status);
		}
	}

	status = hclge_mac_update_stats(hdev);
	if (status)
		dev_err(&hdev->pdev->dev,
			"Update MAC stats fail, status = %d.\n", status);

	status = hclge_32_bit_update_stats(hdev);
	if (status)
		dev_err(&hdev->pdev->dev,
			"Update 32 bit stats fail, status = %d.\n",
			status);

	hclge_update_netstat(&hdev->hw_stats, &handle->kinfo.netdev->stats);
}