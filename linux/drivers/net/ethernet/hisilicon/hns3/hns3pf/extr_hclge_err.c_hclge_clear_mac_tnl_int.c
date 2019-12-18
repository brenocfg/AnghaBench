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
struct hclge_desc {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_TNL_INT_CLR ; 
 int /*<<< orphan*/  HCLGE_OPC_CLEAR_MAC_TNL_INT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_clear_mac_tnl_int(struct hclge_dev *hdev)
{
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CLEAR_MAC_TNL_INT, false);
	desc.data[0] = cpu_to_le32(HCLGE_MAC_TNL_INT_CLR);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}