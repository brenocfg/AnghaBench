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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u8 ;
struct pyra_roccat_report {int type; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct pyra_mouse_event_button {int type; int /*<<< orphan*/  data1; int /*<<< orphan*/  data2; } ;
struct pyra_device {int /*<<< orphan*/  chrdev_minor; int /*<<< orphan*/  actual_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  PYRA_MOUSE_EVENT_BUTTON_PRESS ; 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI 132 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_MACRO 131 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2 130 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_QUICKLAUNCH 129 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_SHORTCUT 128 
 scalar_t__ const PYRA_MOUSE_REPORT_NUMBER_BUTTON ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void pyra_report_to_chrdev(struct pyra_device const *pyra,
		u8 const *data)
{
	struct pyra_roccat_report roccat_report;
	struct pyra_mouse_event_button const *button_event;

	if (data[0] != PYRA_MOUSE_REPORT_NUMBER_BUTTON)
		return;

	button_event = (struct pyra_mouse_event_button const *)data;

	switch (button_event->type) {
	case PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2:
	case PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI:
		roccat_report.type = button_event->type;
		roccat_report.value = button_event->data1;
		roccat_report.key = 0;
		roccat_report_event(pyra->chrdev_minor,
				(uint8_t const *)&roccat_report);
		break;
	case PYRA_MOUSE_EVENT_BUTTON_TYPE_MACRO:
	case PYRA_MOUSE_EVENT_BUTTON_TYPE_SHORTCUT:
	case PYRA_MOUSE_EVENT_BUTTON_TYPE_QUICKLAUNCH:
		if (button_event->data2 == PYRA_MOUSE_EVENT_BUTTON_PRESS) {
			roccat_report.type = button_event->type;
			roccat_report.key = button_event->data1;
			/*
			 * pyra reports profile numbers with range 1-5.
			 * Keeping this behaviour.
			 */
			roccat_report.value = pyra->actual_profile + 1;
			roccat_report_event(pyra->chrdev_minor,
					(uint8_t const *)&roccat_report);
		}
		break;
	}
}