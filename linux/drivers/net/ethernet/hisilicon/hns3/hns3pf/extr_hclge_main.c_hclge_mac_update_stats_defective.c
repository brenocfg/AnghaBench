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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  mac_stats; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_1__ hw_stats; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_MAC_CMD_NUM ; 
 int /*<<< orphan*/  HCLGE_OPC_STATS_MAC ; 
 int HCLGE_RD_FIRST_STATS_NUM ; 
 int HCLGE_RD_OTHER_STATS_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hclge_mac_update_stats_defective(struct hclge_dev *hdev)
{
#define HCLGE_MAC_CMD_NUM 21

	u64 *data = (u64 *)(&hdev->hw_stats.mac_stats);
	struct hclge_desc desc[HCLGE_MAC_CMD_NUM];
	__le64 *desc_data;
	int i, k, n;
	int ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_MAC, true);
	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_MAC_CMD_NUM);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get MAC pkt stats fail, status = %d.\n", ret);

		return ret;
	}

	for (i = 0; i < HCLGE_MAC_CMD_NUM; i++) {
		/* for special opcode 0032, only the first desc has the head */
		if (unlikely(i == 0)) {
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_RD_FIRST_STATS_NUM;
		} else {
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_RD_OTHER_STATS_NUM;
		}

		for (k = 0; k < n; k++) {
			*data += le64_to_cpu(*desc_data);
			data++;
			desc_data++;
		}
	}

	return 0;
}