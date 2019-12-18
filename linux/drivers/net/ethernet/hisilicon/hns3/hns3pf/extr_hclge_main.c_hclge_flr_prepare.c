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
struct hnae3_ae_dev {struct hclge_dev* priv; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  flr_state; int /*<<< orphan*/  default_reset_request; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FLR_WAIT_CNT ; 
 int /*<<< orphan*/  HCLGE_FLR_WAIT_MS ; 
 int /*<<< orphan*/  HNAE3_FLR_DONE ; 
 int /*<<< orphan*/  HNAE3_FLR_DOWN ; 
 int /*<<< orphan*/  HNAE3_FLR_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_reset_event (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_flr_prepare(struct hnae3_ae_dev *ae_dev)
{
#define HCLGE_FLR_WAIT_MS	100
#define HCLGE_FLR_WAIT_CNT	50
	struct hclge_dev *hdev = ae_dev->priv;
	int cnt = 0;

	clear_bit(HNAE3_FLR_DOWN, &hdev->flr_state);
	clear_bit(HNAE3_FLR_DONE, &hdev->flr_state);
	set_bit(HNAE3_FLR_RESET, &hdev->default_reset_request);
	hclge_reset_event(hdev->pdev, NULL);

	while (!test_bit(HNAE3_FLR_DOWN, &hdev->flr_state) &&
	       cnt++ < HCLGE_FLR_WAIT_CNT)
		msleep(HCLGE_FLR_WAIT_MS);

	if (!test_bit(HNAE3_FLR_DOWN, &hdev->flr_state))
		dev_err(&hdev->pdev->dev,
			"flr wait down timeout: %d\n", cnt);
}