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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ num_tc; } ;
struct hclge_dev {TYPE_2__ tm_info; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_bp_setup_hw (struct hclge_dev*,scalar_t__) ; 
 int hclge_mac_pause_setup_hw (struct hclge_dev*) ; 
 int hclge_pause_param_setup_hw (struct hclge_dev*) ; 
 int hclge_pfc_setup_hw (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 

int hclge_pause_setup_hw(struct hclge_dev *hdev)
{
	int ret;
	u8 i;

	ret = hclge_pause_param_setup_hw(hdev);
	if (ret)
		return ret;

	ret = hclge_mac_pause_setup_hw(hdev);
	if (ret)
		return ret;

	/* Only DCB-supported dev supports qset back pressure and pfc cmd */
	if (!hnae3_dev_dcb_supported(hdev))
		return 0;

	/* When MAC is GE Mode, hdev does not support pfc setting */
	ret = hclge_pfc_setup_hw(hdev);
	if (ret)
		dev_warn(&hdev->pdev->dev, "set pfc pause failed:%d\n", ret);

	for (i = 0; i < hdev->tm_info.num_tc; i++) {
		ret = hclge_bp_setup_hw(hdev, i);
		if (ret)
			return ret;
	}

	return 0;
}