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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {void* flag; void* opcode; } ;

/* Variables and functions */
 int HCLGE_CMD_FLAG_IN ; 
 int HCLGE_CMD_FLAG_NO_INTR ; 
 int HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT ; 
 int HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT ; 
 void* cpu_to_le16 (int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_clear_hw_msix_error(struct hclge_dev *hdev,
				     struct hclge_desc *desc, bool is_mpf,
				     u32 bd_num)
{
	if (is_mpf)
		desc[0].opcode =
			cpu_to_le16(HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT);
	else
		desc[0].opcode = cpu_to_le16(HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT);

	desc[0].flag = cpu_to_le16(HCLGE_CMD_FLAG_NO_INTR | HCLGE_CMD_FLAG_IN);

	return hclge_cmd_send(&hdev->hw, &desc[0], bd_num);
}