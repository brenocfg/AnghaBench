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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_stats; } ;
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_1__ hw_stats; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HCLGE_OPC_STATS_MAC_ALL ; 
 size_t HCLGE_RD_FIRST_STATS_NUM ; 
 size_t HCLGE_RD_OTHER_STATS_NUM ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,size_t) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 struct hclge_desc* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hclge_desc*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_mac_update_stats_complete(struct hclge_dev *hdev, u32 desc_num)
{
	u64 *data = (u64 *)(&hdev->hw_stats.mac_stats);
	struct hclge_desc *desc;
	__le64 *desc_data;
	u16 i, k, n;
	int ret;

	/* This may be called inside atomic sections,
	 * so GFP_ATOMIC is more suitalbe here
	 */
	desc = kcalloc(desc_num, sizeof(struct hclge_desc), GFP_ATOMIC);
	if (!desc)
		return -ENOMEM;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_MAC_ALL, true);
	ret = hclge_cmd_send(&hdev->hw, desc, desc_num);
	if (ret) {
		kfree(desc);
		return ret;
	}

	for (i = 0; i < desc_num; i++) {
		/* for special opcode 0034, only the first desc has the head */
		if (i == 0) {
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

	kfree(desc);

	return 0;
}