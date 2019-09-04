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
typedef  int /*<<< orphan*/  uint ;
struct kone_roccat_report {scalar_t__ key; int /*<<< orphan*/  value; int /*<<< orphan*/  event; } ;
struct kone_device {int /*<<< orphan*/  chrdev_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  kone_mouse_event_switch_profile ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kone_profile_report(struct kone_device *kone, uint new_profile)
{
	struct kone_roccat_report roccat_report;

	roccat_report.event = kone_mouse_event_switch_profile;
	roccat_report.value = new_profile;
	roccat_report.key = 0;
	roccat_report_event(kone->chrdev_minor, (uint8_t *)&roccat_report);
}