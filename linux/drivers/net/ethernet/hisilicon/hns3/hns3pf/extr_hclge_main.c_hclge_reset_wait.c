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
struct hclge_dev {int reset_type; TYPE_1__* pdev; int /*<<< orphan*/  hw; int /*<<< orphan*/  flr_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ HCLGE_FUN_RST_ING ; 
 scalar_t__ HCLGE_FUN_RST_ING_B ; 
 scalar_t__ HCLGE_GLOBAL_RESET_BIT ; 
 scalar_t__ HCLGE_GLOBAL_RESET_REG ; 
 scalar_t__ HCLGE_IMP_RESET_BIT ; 
 scalar_t__ HCLGE_RESET_WAIT_CNT ; 
 int /*<<< orphan*/  HCLGE_RESET_WATI_MS ; 
 int /*<<< orphan*/  HNAE3_FLR_DONE ; 
#define  HNAE3_FLR_RESET 131 
#define  HNAE3_FUNC_RESET 130 
#define  HNAE3_GLOBAL_RESET 129 
#define  HNAE3_IMP_RESET 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int const) ; 
 scalar_t__ hclge_read_dev (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hnae3_get_bit (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_reset_wait(struct hclge_dev *hdev)
{
#define HCLGE_RESET_WATI_MS	100
#define HCLGE_RESET_WAIT_CNT	200
	u32 val, reg, reg_bit;
	u32 cnt = 0;

	switch (hdev->reset_type) {
	case HNAE3_IMP_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_IMP_RESET_BIT;
		break;
	case HNAE3_GLOBAL_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_GLOBAL_RESET_BIT;
		break;
	case HNAE3_FUNC_RESET:
		reg = HCLGE_FUN_RST_ING;
		reg_bit = HCLGE_FUN_RST_ING_B;
		break;
	case HNAE3_FLR_RESET:
		break;
	default:
		dev_err(&hdev->pdev->dev,
			"Wait for unsupported reset type: %d\n",
			hdev->reset_type);
		return -EINVAL;
	}

	if (hdev->reset_type == HNAE3_FLR_RESET) {
		while (!test_bit(HNAE3_FLR_DONE, &hdev->flr_state) &&
		       cnt++ < HCLGE_RESET_WAIT_CNT)
			msleep(HCLGE_RESET_WATI_MS);

		if (!test_bit(HNAE3_FLR_DONE, &hdev->flr_state)) {
			dev_err(&hdev->pdev->dev,
				"flr wait timeout: %d\n", cnt);
			return -EBUSY;
		}

		return 0;
	}

	val = hclge_read_dev(&hdev->hw, reg);
	while (hnae3_get_bit(val, reg_bit) && cnt < HCLGE_RESET_WAIT_CNT) {
		msleep(HCLGE_RESET_WATI_MS);
		val = hclge_read_dev(&hdev->hw, reg);
		cnt++;
	}

	if (cnt >= HCLGE_RESET_WAIT_CNT) {
		dev_warn(&hdev->pdev->dev,
			 "Wait for reset timeout: %d\n", hdev->reset_type);
		return -EBUSY;
	}

	return 0;
}