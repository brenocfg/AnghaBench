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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_sfp_info_cmd {int /*<<< orphan*/  speed; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCLGE_OPC_GET_SFP_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_get_sfp_speed(struct hclge_dev *hdev, u32 *speed)
{
	struct hclge_sfp_info_cmd *resp;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GET_SFP_INFO, true);
	resp = (struct hclge_sfp_info_cmd *)desc.data;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret == -EOPNOTSUPP) {
		dev_warn(&hdev->pdev->dev,
			 "IMP do not support get SFP speed %d\n", ret);
		return ret;
	} else if (ret) {
		dev_err(&hdev->pdev->dev, "get sfp speed failed %d\n", ret);
		return ret;
	}

	*speed = le32_to_cpu(resp->speed);

	return 0;
}