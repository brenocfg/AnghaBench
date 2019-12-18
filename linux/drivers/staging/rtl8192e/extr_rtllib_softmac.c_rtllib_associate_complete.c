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
struct rtllib_device {int /*<<< orphan*/  associate_complete_wq; int /*<<< orphan*/  state; int /*<<< orphan*/  associate_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLLIB_LINKED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_sta_send_associnfo (struct rtllib_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtllib_associate_complete(struct rtllib_device *ieee)
{
	del_timer_sync(&ieee->associate_timer);

	ieee->state = RTLLIB_LINKED;
	rtllib_sta_send_associnfo(ieee);

	schedule_work(&ieee->associate_complete_wq);
}