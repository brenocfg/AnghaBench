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

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MISC_RESET_STS_REG ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_CMDQ_SRC_REG ; 
#define  HCLGE_VECTOR0_EVENT_MBX 129 
#define  HCLGE_VECTOR0_EVENT_RST 128 
 int /*<<< orphan*/  hclge_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_clear_event_cause(struct hclge_dev *hdev, u32 event_type,
				    u32 regclr)
{
	switch (event_type) {
	case HCLGE_VECTOR0_EVENT_RST:
		hclge_write_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG, regclr);
		break;
	case HCLGE_VECTOR0_EVENT_MBX:
		hclge_write_dev(&hdev->hw, HCLGE_VECTOR0_CMDQ_SRC_REG, regclr);
		break;
	default:
		break;
	}
}