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
struct savu_roccat_report {int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
struct savu_mouse_report_special {int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
struct roccat_common2_device {int /*<<< orphan*/  chrdev_minor; } ;

/* Variables and functions */
 scalar_t__ const SAVU_MOUSE_REPORT_NUMBER_SPECIAL ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void savu_report_to_chrdev(struct roccat_common2_device const *savu,
		u8 const *data)
{
	struct savu_roccat_report roccat_report;
	struct savu_mouse_report_special const *special_report;

	if (data[0] != SAVU_MOUSE_REPORT_NUMBER_SPECIAL)
		return;

	special_report = (struct savu_mouse_report_special const *)data;

	roccat_report.type = special_report->type;
	roccat_report.data[0] = special_report->data[0];
	roccat_report.data[1] = special_report->data[1];
	roccat_report_event(savu->chrdev_minor,
			(uint8_t const *)&roccat_report);
}