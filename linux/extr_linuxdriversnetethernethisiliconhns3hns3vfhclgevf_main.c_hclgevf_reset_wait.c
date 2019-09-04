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
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGEVF_FUN_RST_ING ; 
 int /*<<< orphan*/  HCLGEVF_FUN_RST_ING_B ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hclgevf_reset_wait(struct hclgevf_dev *hdev)
{
#define HCLGEVF_RESET_WAIT_MS	500
#define HCLGEVF_RESET_WAIT_CNT	20
	u32 val, cnt = 0;

	/* wait to check the hardware reset completion status */
	val = hclgevf_read_dev(&hdev->hw, HCLGEVF_FUN_RST_ING);
	while (hnae3_get_bit(val, HCLGEVF_FUN_RST_ING_B) &&
	       (cnt < HCLGEVF_RESET_WAIT_CNT)) {
		msleep(HCLGEVF_RESET_WAIT_MS);
		val = hclgevf_read_dev(&hdev->hw, HCLGEVF_FUN_RST_ING);
		cnt++;
	}

	/* hardware completion status should be available by this time */
	if (cnt >= HCLGEVF_RESET_WAIT_CNT) {
		dev_warn(&hdev->pdev->dev,
			 "could'nt get reset done status from h/w, timeout!\n");
		return -EBUSY;
	}

	/* we will wait a bit more to let reset of the stack to complete. This
	 * might happen in case reset assertion was made by PF. Yes, this also
	 * means we might end up waiting bit more even for VF reset.
	 */
	msleep(5000);

	return 0;
}