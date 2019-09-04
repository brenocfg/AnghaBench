#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dev_pm_ops {int dummy; } ;
struct TYPE_3__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int /*<<< orphan*/ * pm_callback_t ;

/* Variables and functions */

__attribute__((used)) static pm_callback_t pm_late_early_op(const struct dev_pm_ops *ops,
				      pm_message_t state)
{
	switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		return ops->suspend_late;
	case PM_EVENT_RESUME:
		return ops->resume_early;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBERNATE_CALLBACKS
	case PM_EVENT_FREEZE:
	case PM_EVENT_QUIESCE:
		return ops->freeze_late;
	case PM_EVENT_HIBERNATE:
		return ops->poweroff_late;
	case PM_EVENT_THAW:
	case PM_EVENT_RECOVER:
		return ops->thaw_early;
	case PM_EVENT_RESTORE:
		return ops->restore_early;
#endif /* CONFIG_HIBERNATE_CALLBACKS */
	}

	return NULL;
}