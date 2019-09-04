#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_LID ; 
 int /*<<< orphan*/  input_report_switch (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  lid_open ; 
 TYPE_1__* lid_switch_idev ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_lid_state(void)
{
	if (!!test_bit(SW_LID, lid_switch_idev->sw) == !lid_open)
		return; /* Nothing new to report. */

	input_report_switch(lid_switch_idev, SW_LID, !lid_open);
	input_sync(lid_switch_idev);
	pm_wakeup_event(&lid_switch_idev->dev, 0);
}