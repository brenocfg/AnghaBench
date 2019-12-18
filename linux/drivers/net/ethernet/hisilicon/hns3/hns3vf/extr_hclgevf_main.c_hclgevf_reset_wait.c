#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ io_base; } ;
struct hclgevf_dev {scalar_t__ reset_type; TYPE_1__* pdev; TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_RESET_WAIT_CNT ; 
 int /*<<< orphan*/  HCLGEVF_RESET_WAIT_TIMEOUT_US ; 
 int /*<<< orphan*/  HCLGEVF_RESET_WAIT_US ; 
 scalar_t__ HCLGEVF_RST_ING ; 
 int HCLGEVF_RST_ING_BITS ; 
 scalar_t__ HCLGEVF_VF_RST_ING ; 
 int HCLGEVF_VF_RST_ING_BIT ; 
 scalar_t__ HNAE3_FLR_RESET ; 
 scalar_t__ HNAE3_VF_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_flr_poll_timeout (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_reset_wait(struct hclgevf_dev *hdev)
{
#define HCLGEVF_RESET_WAIT_US	20000
#define HCLGEVF_RESET_WAIT_CNT	2000
#define HCLGEVF_RESET_WAIT_TIMEOUT_US	\
	(HCLGEVF_RESET_WAIT_US * HCLGEVF_RESET_WAIT_CNT)

	u32 val;
	int ret;

	if (hdev->reset_type == HNAE3_FLR_RESET)
		return hclgevf_flr_poll_timeout(hdev,
						HCLGEVF_RESET_WAIT_US,
						HCLGEVF_RESET_WAIT_CNT);
	else if (hdev->reset_type == HNAE3_VF_RESET)
		ret = readl_poll_timeout(hdev->hw.io_base +
					 HCLGEVF_VF_RST_ING, val,
					 !(val & HCLGEVF_VF_RST_ING_BIT),
					 HCLGEVF_RESET_WAIT_US,
					 HCLGEVF_RESET_WAIT_TIMEOUT_US);
	else
		ret = readl_poll_timeout(hdev->hw.io_base +
					 HCLGEVF_RST_ING, val,
					 !(val & HCLGEVF_RST_ING_BITS),
					 HCLGEVF_RESET_WAIT_US,
					 HCLGEVF_RESET_WAIT_TIMEOUT_US);

	/* hardware completion status should be available by this time */
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"could'nt get reset done status from h/w, timeout!\n");
		return ret;
	}

	/* we will wait a bit more to let reset of the stack to complete. This
	 * might happen in case reset assertion was made by PF. Yes, this also
	 * means we might end up waiting bit more even for VF reset.
	 */
	msleep(5000);

	return 0;
}