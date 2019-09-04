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
typedef  int u32 ;
struct hclge_dev {int reset_type; TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int HCLGE_CORE_RESET_BIT ; 
 int HCLGE_FUN_RST_ING ; 
 int HCLGE_FUN_RST_ING_B ; 
 int HCLGE_GLOBAL_RESET_BIT ; 
 int HCLGE_GLOBAL_RESET_REG ; 
#define  HNAE3_CORE_RESET 130 
#define  HNAE3_FUNC_RESET 129 
#define  HNAE3_GLOBAL_RESET 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_read_dev (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hnae3_get_bit (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hclge_reset_wait(struct hclge_dev *hdev)
{
#define HCLGE_RESET_WATI_MS	100
#define HCLGE_RESET_WAIT_CNT	5
	u32 val, reg, reg_bit;
	u32 cnt = 0;

	switch (hdev->reset_type) {
	case HNAE3_GLOBAL_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_GLOBAL_RESET_BIT;
		break;
	case HNAE3_CORE_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_CORE_RESET_BIT;
		break;
	case HNAE3_FUNC_RESET:
		reg = HCLGE_FUN_RST_ING;
		reg_bit = HCLGE_FUN_RST_ING_B;
		break;
	default:
		dev_err(&hdev->pdev->dev,
			"Wait for unsupported reset type: %d\n",
			hdev->reset_type);
		return -EINVAL;
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