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
struct hclge_sfp_info_cmd {int /*<<< orphan*/  active_fec; int /*<<< orphan*/  autoneg_ability; int /*<<< orphan*/  autoneg; scalar_t__ speed_ability; scalar_t__ module_type; scalar_t__ speed; void* query_type; } ;
struct hclge_mac {void* speed_type; int /*<<< orphan*/  fec_mode; int /*<<< orphan*/  support_autoneg; int /*<<< orphan*/  autoneg; void* speed_ability; void* module_type; void* speed; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCLGE_OPC_GET_SFP_INFO ; 
 void* QUERY_ACTIVE_SPEED ; 
 void* QUERY_SFP_SPEED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 void* le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static int hclge_get_sfp_info(struct hclge_dev *hdev, struct hclge_mac *mac)
{
	struct hclge_sfp_info_cmd *resp;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GET_SFP_INFO, true);
	resp = (struct hclge_sfp_info_cmd *)desc.data;

	resp->query_type = QUERY_ACTIVE_SPEED;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret == -EOPNOTSUPP) {
		dev_warn(&hdev->pdev->dev,
			 "IMP does not support get SFP info %d\n", ret);
		return ret;
	} else if (ret) {
		dev_err(&hdev->pdev->dev, "get sfp info failed %d\n", ret);
		return ret;
	}

	mac->speed = le32_to_cpu(resp->speed);
	/* if resp->speed_ability is 0, it means it's an old version
	 * firmware, do not update these params
	 */
	if (resp->speed_ability) {
		mac->module_type = le32_to_cpu(resp->module_type);
		mac->speed_ability = le32_to_cpu(resp->speed_ability);
		mac->autoneg = resp->autoneg;
		mac->support_autoneg = resp->autoneg_ability;
		mac->speed_type = QUERY_ACTIVE_SPEED;
		if (!resp->active_fec)
			mac->fec_mode = 0;
		else
			mac->fec_mode = BIT(resp->active_fec);
	} else {
		mac->speed_type = QUERY_SFP_SPEED;
	}

	return 0;
}