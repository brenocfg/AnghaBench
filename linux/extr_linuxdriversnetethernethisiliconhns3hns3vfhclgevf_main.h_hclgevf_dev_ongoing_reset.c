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
struct TYPE_2__ {scalar_t__ reset_level; } ;
struct hclgevf_dev {TYPE_1__ nic; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_RST_HANDLING ; 
 scalar_t__ HNAE3_VF_RESET ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool hclgevf_dev_ongoing_reset(struct hclgevf_dev *hdev)
{
	return (hdev &&
		(test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state)) &&
		(hdev->nic.reset_level == HNAE3_VF_RESET));
}