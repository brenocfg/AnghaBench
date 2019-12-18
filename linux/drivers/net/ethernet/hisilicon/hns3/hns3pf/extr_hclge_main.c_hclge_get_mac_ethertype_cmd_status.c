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
typedef  int u8 ;
typedef  int u16 ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
#define  HCLGE_ETHERTYPE_ALREADY_ADD 131 
#define  HCLGE_ETHERTYPE_KEY_CONFLICT 130 
#define  HCLGE_ETHERTYPE_MGR_TBL_OVERFLOW 129 
#define  HCLGE_ETHERTYPE_SUCCESS_ADD 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int hclge_get_mac_ethertype_cmd_status(struct hclge_dev *hdev,
					      u16 cmdq_resp, u8 resp_code)
{
#define HCLGE_ETHERTYPE_SUCCESS_ADD		0
#define HCLGE_ETHERTYPE_ALREADY_ADD		1
#define HCLGE_ETHERTYPE_MGR_TBL_OVERFLOW	2
#define HCLGE_ETHERTYPE_KEY_CONFLICT		3

	int return_status;

	if (cmdq_resp) {
		dev_err(&hdev->pdev->dev,
			"cmdq execute failed for get_mac_ethertype_cmd_status, status=%d.\n",
			cmdq_resp);
		return -EIO;
	}

	switch (resp_code) {
	case HCLGE_ETHERTYPE_SUCCESS_ADD:
	case HCLGE_ETHERTYPE_ALREADY_ADD:
		return_status = 0;
		break;
	case HCLGE_ETHERTYPE_MGR_TBL_OVERFLOW:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for manager table overflow.\n");
		return_status = -EIO;
		break;
	case HCLGE_ETHERTYPE_KEY_CONFLICT:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for key conflict.\n");
		return_status = -EIO;
		break;
	default:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for undefined, code=%d.\n",
			resp_code);
		return_status = -EIO;
	}

	return return_status;
}