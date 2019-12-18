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
struct timer_list {int dummy; } ;
struct brcmf_btcoex_info {int timer_on; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_btcoex_info* bt_local ; 
 struct brcmf_btcoex_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void brcmf_btcoex_timerfunc(struct timer_list *t)
{
	struct brcmf_btcoex_info *bt_local = from_timer(bt_local, t, timer);
	brcmf_dbg(TRACE, "enter\n");

	bt_local->timer_on = false;
	schedule_work(&bt_local->work);
}