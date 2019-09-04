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
struct koneplus_roccat_report {scalar_t__ type; scalar_t__ data2; scalar_t__ profile; int /*<<< orphan*/  data1; } ;
struct koneplus_mouse_report_button {scalar_t__ type; scalar_t__ data2; int /*<<< orphan*/  data1; } ;
struct koneplus_device {int /*<<< orphan*/  chrdev_minor; scalar_t__ actual_profile; } ;

/* Variables and functions */
 scalar_t__ KONEPLUS_MOUSE_REPORT_BUTTON_ACTION_PRESS ; 
 scalar_t__ KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH ; 
 scalar_t__ KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_TIMER ; 
 scalar_t__ const KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void koneplus_report_to_chrdev(struct koneplus_device const *koneplus,
		u8 const *data)
{
	struct koneplus_roccat_report roccat_report;
	struct koneplus_mouse_report_button const *button_report;

	if (data[0] != KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON)
		return;

	button_report = (struct koneplus_mouse_report_button const *)data;

	if ((button_report->type == KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH ||
			button_report->type == KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_TIMER) &&
			button_report->data2 != KONEPLUS_MOUSE_REPORT_BUTTON_ACTION_PRESS)
		return;

	roccat_report.type = button_report->type;
	roccat_report.data1 = button_report->data1;
	roccat_report.data2 = button_report->data2;
	roccat_report.profile = koneplus->actual_profile + 1;
	roccat_report_event(koneplus->chrdev_minor,
			(uint8_t const *)&roccat_report);
}