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
typedef  scalar_t__ u32 ;
struct hclge_dev {int reset_type; int /*<<< orphan*/  misc_vector; int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCLGE_MISC_RESET_STS_REG ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_GLOBALRESET_INT_B ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_IMPRESET_INT_B ; 
#define  HNAE3_GLOBAL_RESET 129 
#define  HNAE3_IMP_RESET 128 
 int /*<<< orphan*/  hclge_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclge_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hclge_clear_reset_cause(struct hclge_dev *hdev)
{
	u32 clearval = 0;

	switch (hdev->reset_type) {
	case HNAE3_IMP_RESET:
		clearval = BIT(HCLGE_VECTOR0_IMPRESET_INT_B);
		break;
	case HNAE3_GLOBAL_RESET:
		clearval = BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B);
		break;
	default:
		break;
	}

	if (!clearval)
		return;

	/* For revision 0x20, the reset interrupt source
	 * can only be cleared after hardware reset done
	 */
	if (hdev->pdev->revision == 0x20)
		hclge_write_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG,
				clearval);

	hclge_enable_vector(&hdev->misc_vector, true);
}