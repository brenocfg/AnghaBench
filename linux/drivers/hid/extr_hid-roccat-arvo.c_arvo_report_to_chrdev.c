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
typedef  int /*<<< orphan*/  u8 ;
struct arvo_special_report {int event; } ;
struct arvo_roccat_report {int button; int /*<<< orphan*/  action; int /*<<< orphan*/  profile; } ;
struct arvo_device {int /*<<< orphan*/  chrdev_minor; int /*<<< orphan*/  actual_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARVO_ROCCAT_REPORT_ACTION_PRESS ; 
 int /*<<< orphan*/  ARVO_ROCCAT_REPORT_ACTION_RELEASE ; 
 int ARVO_SPECIAL_REPORT_EVENT_ACTION_PRESS ; 
 int ARVO_SPECIAL_REPORT_EVENT_MASK_ACTION ; 
 int ARVO_SPECIAL_REPORT_EVENT_MASK_BUTTON ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void arvo_report_to_chrdev(struct arvo_device const *arvo,
		u8 const *data)
{
	struct arvo_special_report const *special_report;
	struct arvo_roccat_report roccat_report;

	special_report = (struct arvo_special_report const *)data;

	roccat_report.profile = arvo->actual_profile;
	roccat_report.button = special_report->event &
			ARVO_SPECIAL_REPORT_EVENT_MASK_BUTTON;
	if ((special_report->event & ARVO_SPECIAL_REPORT_EVENT_MASK_ACTION) ==
			ARVO_SPECIAL_REPORT_EVENT_ACTION_PRESS)
		roccat_report.action = ARVO_ROCCAT_REPORT_ACTION_PRESS;
	else
		roccat_report.action = ARVO_ROCCAT_REPORT_ACTION_RELEASE;

	roccat_report_event(arvo->chrdev_minor,
			(uint8_t const *)&roccat_report);
}