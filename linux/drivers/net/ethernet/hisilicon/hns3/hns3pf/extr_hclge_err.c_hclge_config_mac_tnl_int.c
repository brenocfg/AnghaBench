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
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {void** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_TNL_INT_EN ; 
 int /*<<< orphan*/  HCLGE_MAC_TNL_INT_EN_MASK ; 
 int /*<<< orphan*/  HCLGE_OPC_MAC_TNL_INT_EN ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

int hclge_config_mac_tnl_int(struct hclge_dev *hdev, bool en)
{
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_TNL_INT_EN, false);
	if (en)
		desc.data[0] = cpu_to_le32(HCLGE_MAC_TNL_INT_EN);
	else
		desc.data[0] = 0;

	desc.data[1] = cpu_to_le32(HCLGE_MAC_TNL_INT_EN_MASK);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}