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
struct hclge_dev {TYPE_1__* pdev; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hclge_cfg_mac_mode (struct hclge_dev*,int) ; 
 int hclge_cfg_serdes_loopback (struct hclge_dev*,int,int) ; 
 int hclge_mac_phy_link_status_wait (struct hclge_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_serdes_loopback(struct hclge_dev *hdev, bool en,
				     enum hnae3_loop loop_mode)
{
	int ret;

	ret = hclge_cfg_serdes_loopback(hdev, en, loop_mode);
	if (ret)
		return ret;

	hclge_cfg_mac_mode(hdev, en);

	ret = hclge_mac_phy_link_status_wait(hdev, en, FALSE);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"serdes loopback config mac mode timeout\n");

	return ret;
}