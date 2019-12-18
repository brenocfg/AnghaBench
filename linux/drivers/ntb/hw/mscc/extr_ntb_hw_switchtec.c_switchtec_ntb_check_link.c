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
struct switchtec_ntb {int link_force_down; int /*<<< orphan*/  check_link_status_work; } ;
typedef  enum switchtec_msg { ____Placeholder_switchtec_msg } switchtec_msg ;

/* Variables and functions */
 int MSG_LINK_FORCE_DOWN ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void switchtec_ntb_check_link(struct switchtec_ntb *sndev,
				      enum switchtec_msg msg)
{
	if (msg == MSG_LINK_FORCE_DOWN)
		sndev->link_force_down = true;

	schedule_work(&sndev->check_link_status_work);
}