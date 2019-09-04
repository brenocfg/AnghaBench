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
struct TYPE_3__ {int /*<<< orphan*/  all_64_bit_stats; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_1__ hw_stats; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_STATS_64_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hclge_64_bit_update_stats(struct hclge_dev *hdev)
{
#define HCLGE_64_BIT_CMD_NUM 5
#define HCLGE_64_BIT_RTN_DATANUM 4
	u64 *data = (u64 *)(&hdev->hw_stats.all_64_bit_stats);
	struct hclge_desc desc[HCLGE_64_BIT_CMD_NUM];
	__le64 *desc_data;
	int i, k, n;
	int ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_64_BIT, true);
	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_64_BIT_CMD_NUM);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get 64 bit pkt stats fail, status = %d.\n", ret);
		return ret;
	}

	for (i = 0; i < HCLGE_64_BIT_CMD_NUM; i++) {
		if (unlikely(i == 0)) {
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_64_BIT_RTN_DATANUM - 1;
		} else {
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_64_BIT_RTN_DATANUM;
		}
		for (k = 0; k < n; k++) {
			*data++ += le64_to_cpu(*desc_data);
			desc_data++;
		}
	}

	return 0;
}