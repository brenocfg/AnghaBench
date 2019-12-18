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
struct udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_exit ; 
 int /*<<< orphan*/  on_pollstall_exit ; 
 int /*<<< orphan*/  stop_pollstall_timer ; 
 int /*<<< orphan*/  stop_timer ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * udc ; 
 int /*<<< orphan*/  udc_pollstall_timer ; 
 int /*<<< orphan*/  udc_timer ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void udc_remove(struct udc *dev)
{
	/* remove timer */
	stop_timer++;
	if (timer_pending(&udc_timer))
		wait_for_completion(&on_exit);
	del_timer_sync(&udc_timer);
	/* remove pollstall timer */
	stop_pollstall_timer++;
	if (timer_pending(&udc_pollstall_timer))
		wait_for_completion(&on_pollstall_exit);
	del_timer_sync(&udc_pollstall_timer);
	udc = NULL;
}