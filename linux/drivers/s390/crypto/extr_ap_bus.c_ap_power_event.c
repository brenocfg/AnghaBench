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
 int NOTIFY_DONE ; 
#define  PM_HIBERNATION_PREPARE 131 
#define  PM_POST_HIBERNATION 130 
#define  PM_POST_SUSPEND 129 
#define  PM_SUSPEND_PREPARE 128 
 int /*<<< orphan*/  ap_bus_resume () ; 
 int /*<<< orphan*/  ap_bus_suspend () ; 

__attribute__((used)) static int ap_power_event(struct notifier_block *this, unsigned long event,
			  void *ptr)
{
	switch (event) {
	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		ap_bus_suspend();
		break;
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		ap_bus_resume();
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}