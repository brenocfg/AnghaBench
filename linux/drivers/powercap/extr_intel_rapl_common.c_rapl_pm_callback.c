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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
#define  PM_POST_SUSPEND 129 
#define  PM_SUSPEND_PREPARE 128 
 int /*<<< orphan*/  power_limit_state_restore () ; 
 int /*<<< orphan*/  power_limit_state_save () ; 

__attribute__((used)) static int rapl_pm_callback(struct notifier_block *nb,
			    unsigned long mode, void *_unused)
{
	switch (mode) {
	case PM_SUSPEND_PREPARE:
		power_limit_state_save();
		break;
	case PM_POST_SUSPEND:
		power_limit_state_restore();
		break;
	}
	return NOTIFY_OK;
}