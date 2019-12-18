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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclge_mac_pause_setup_hw (struct hclge_dev*) ; 
 int hclge_pause_param_setup_hw (struct hclge_dev*) ; 
 int hclge_pfc_setup_hw (struct hclge_dev*) ; 
 int hclge_tm_bp_setup (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 

int hclge_pause_setup_hw(struct hclge_dev *hdev, bool init)
{
	int ret;

	ret = hclge_pause_param_setup_hw(hdev);
	if (ret)
		return ret;

	ret = hclge_mac_pause_setup_hw(hdev);
	if (ret)
		return ret;

	/* Only DCB-supported dev supports qset back pressure and pfc cmd */
	if (!hnae3_dev_dcb_supported(hdev))
		return 0;

	/* GE MAC does not support PFC, when driver is initializing and MAC
	 * is in GE Mode, ignore the error here, otherwise initialization
	 * will fail.
	 */
	ret = hclge_pfc_setup_hw(hdev);
	if (init && ret == -EOPNOTSUPP)
		dev_warn(&hdev->pdev->dev, "GE MAC does not support pfc\n");
	else if (ret) {
		dev_err(&hdev->pdev->dev, "config pfc failed! ret = %d\n",
			ret);
		return ret;
	}

	return hclge_tm_bp_setup(hdev);
}