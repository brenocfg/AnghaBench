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
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  flr_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HNAE3_FLR_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int hclgevf_flr_poll_timeout(struct hclgevf_dev *hdev,
				    unsigned long delay_us,
				    unsigned long wait_cnt)
{
	unsigned long cnt = 0;

	while (!test_bit(HNAE3_FLR_DONE, &hdev->flr_state) &&
	       cnt++ < wait_cnt)
		usleep_range(delay_us, delay_us * 2);

	if (!test_bit(HNAE3_FLR_DONE, &hdev->flr_state)) {
		dev_err(&hdev->pdev->dev,
			"flr wait timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}