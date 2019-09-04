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
typedef  scalar_t__ u8 ;
struct kovaplus_mouse_report_button {int type; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;
struct kovaplus_device {int /*<<< orphan*/  actual_y_sensitivity; int /*<<< orphan*/  actual_x_sensitivity; int /*<<< orphan*/  actual_cpi; } ;

/* Variables and functions */
#define  KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI 130 
#define  KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE_1 129 
#define  KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY 128 
 scalar_t__ const KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON ; 
 int /*<<< orphan*/  kovaplus_convert_event_cpi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kovaplus_profile_activated (struct kovaplus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kovaplus_keep_values_up_to_date(struct kovaplus_device *kovaplus,
		u8 const *data)
{
	struct kovaplus_mouse_report_button const *button_report;

	if (data[0] != KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON)
		return;

	button_report = (struct kovaplus_mouse_report_button const *)data;

	switch (button_report->type) {
	case KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE_1:
		kovaplus_profile_activated(kovaplus, button_report->data1 - 1);
		break;
	case KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI:
		kovaplus->actual_cpi = kovaplus_convert_event_cpi(button_report->data1);
		break;
	case KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY:
		kovaplus->actual_x_sensitivity = button_report->data1;
		kovaplus->actual_y_sensitivity = button_report->data2;
		break;
	default:
		break;
	}
}