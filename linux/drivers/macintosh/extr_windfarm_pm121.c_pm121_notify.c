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
struct wf_sensor {int /*<<< orphan*/  name; } ;
struct wf_control {int /*<<< orphan*/  name; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  WF_EVENT_NEW_CONTROL 130 
#define  WF_EVENT_NEW_SENSOR 129 
#define  WF_EVENT_TICK 128 
 int /*<<< orphan*/  pm121_all_controls_ok ; 
 int /*<<< orphan*/  pm121_all_sensors_ok ; 
 int /*<<< orphan*/  pm121_new_control (void*) ; 
 int /*<<< orphan*/  pm121_new_sensor (void*) ; 
 int /*<<< orphan*/  pm121_tick () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm121_notify(struct notifier_block *self,
			unsigned long event, void *data)
{
	switch (event) {
	case WF_EVENT_NEW_CONTROL:
		pr_debug("pm121: new control %s detected\n",
			 ((struct wf_control *)data)->name);
		pm121_new_control(data);
		break;
	case WF_EVENT_NEW_SENSOR:
		pr_debug("pm121: new sensor %s detected\n",
			 ((struct wf_sensor *)data)->name);
		pm121_new_sensor(data);
		break;
	case WF_EVENT_TICK:
		if (pm121_all_controls_ok && pm121_all_sensors_ok)
			pm121_tick();
		break;
	}

	return 0;
}