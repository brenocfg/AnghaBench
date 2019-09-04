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
struct net_device_stats {int dummy; } ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_tqps_update_stats (struct hnae3_handle*) ; 

__attribute__((used)) static void hclgevf_update_stats(struct hnae3_handle *handle,
				 struct net_device_stats *net_stats)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	int status;

	status = hclgevf_tqps_update_stats(handle);
	if (status)
		dev_err(&hdev->pdev->dev,
			"VF update of TQPS stats fail, status = %d.\n",
			status);
}