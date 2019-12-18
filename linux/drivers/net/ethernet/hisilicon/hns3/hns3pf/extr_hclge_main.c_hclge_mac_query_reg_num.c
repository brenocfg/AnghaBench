#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_QUERY_MAC_REG_NUM ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_mac_query_reg_num(struct hclge_dev *hdev, u32 *desc_num)
{
	struct hclge_desc desc;
	__le32 *desc_data;
	u32 reg_num;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_MAC_REG_NUM, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		return ret;

	desc_data = (__le32 *)(&desc.data[0]);
	reg_num = le32_to_cpu(*desc_data);

	*desc_num = 1 + ((reg_num - 3) >> 2) +
		    (u32)(((reg_num - 3) & 0x3) ? 1 : 0);

	return 0;
}