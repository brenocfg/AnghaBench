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
struct hnae3_handle {scalar_t__ client; } ;
struct hclge_dev {TYPE_2__* pdev; TYPE_1__* vport; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_mac_update_stats (struct hclge_dev*) ; 
 int hclge_tqps_update_stats (struct hnae3_handle*) ; 

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
}