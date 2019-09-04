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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_LID_DETECT_ON ; 
 int /*<<< orphan*/  yeeloong_report_lid_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yeeloong_lid_update_task(struct work_struct *work)
{
	if (yeeloong_report_lid_status)
		yeeloong_report_lid_status(BIT_LID_DETECT_ON);
}