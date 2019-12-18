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
typedef  int u8 ;
struct pyra_mouse_event_button {int /*<<< orphan*/  data1; int /*<<< orphan*/  type; } ;
struct pyra_device {int /*<<< orphan*/  actual_cpi; } ;

/* Variables and functions */
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI 130 
#define  PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2 129 
#define  PYRA_MOUSE_REPORT_NUMBER_BUTTON 128 
 int /*<<< orphan*/  profile_activated (struct pyra_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pyra_keep_values_up_to_date(struct pyra_device *pyra,
		u8 const *data)
{
	struct pyra_mouse_event_button const *button_event;

	switch (data[0]) {
	case PYRA_MOUSE_REPORT_NUMBER_BUTTON:
		button_event = (struct pyra_mouse_event_button const *)data;
		switch (button_event->type) {
		case PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2:
			profile_activated(pyra, button_event->data1 - 1);
			break;
		case PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI:
			pyra->actual_cpi = button_event->data1;
			break;
		}
		break;
	}
}