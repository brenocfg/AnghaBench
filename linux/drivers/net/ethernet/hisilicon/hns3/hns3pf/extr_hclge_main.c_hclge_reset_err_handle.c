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
struct TYPE_3__ {scalar_t__ reset_fail_cnt; } ;
struct hclge_dev {scalar_t__ reset_pending; TYPE_2__* pdev; TYPE_1__ rst_stats; int /*<<< orphan*/  reset_type; int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MISC_VECTOR_INT_STS ; 
 int HCLGE_RESET_INT_M ; 
 scalar_t__ MAX_RESET_FAIL_CNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hclge_clear_reset_cause (struct hclge_dev*) ; 
 int hclge_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_handshake (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool hclge_reset_err_handle(struct hclge_dev *hdev)
{
#define MAX_RESET_FAIL_CNT 5

	if (hdev->reset_pending) {
		dev_info(&hdev->pdev->dev, "Reset pending %lu\n",
			 hdev->reset_pending);
		return true;
	} else if (hclge_read_dev(&hdev->hw, HCLGE_MISC_VECTOR_INT_STS) &
		   HCLGE_RESET_INT_M) {
		dev_info(&hdev->pdev->dev,
			 "reset failed because new reset interrupt\n");
		hclge_clear_reset_cause(hdev);
		return false;
	} else if (hdev->rst_stats.reset_fail_cnt < MAX_RESET_FAIL_CNT) {
		hdev->rst_stats.reset_fail_cnt++;
		set_bit(hdev->reset_type, &hdev->reset_pending);
		dev_info(&hdev->pdev->dev,
			 "re-schedule reset task(%d)\n",
			 hdev->rst_stats.reset_fail_cnt);
		return true;
	}

	hclge_clear_reset_cause(hdev);

	/* recover the handshake status when reset fail */
	hclge_reset_handshake(hdev, true);

	dev_err(&hdev->pdev->dev, "Reset fail!\n");
	return false;
}