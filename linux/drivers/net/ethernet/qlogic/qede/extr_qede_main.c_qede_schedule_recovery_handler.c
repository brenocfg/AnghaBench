#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qede_dev {scalar_t__ state; int /*<<< orphan*/  sp_task; int /*<<< orphan*/  sp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  QEDE_SP_RECOVERY ; 
 scalar_t__ QEDE_STATE_RECOVERY ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_schedule_recovery_handler(void *dev)
{
	struct qede_dev *edev = dev;

	if (edev->state == QEDE_STATE_RECOVERY) {
		DP_NOTICE(edev,
			  "Avoid scheduling a recovery handling since already in recovery state\n");
		return;
	}

	set_bit(QEDE_SP_RECOVERY, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);

	DP_INFO(edev, "Scheduled a recovery handler\n");
}