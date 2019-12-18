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
struct user_evtchn {int /*<<< orphan*/  node; } ;
struct per_user_data {int /*<<< orphan*/  evtchns; int /*<<< orphan*/  nr_evtchns; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct user_evtchn*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void del_evtchn(struct per_user_data *u, struct user_evtchn *evtchn)
{
	u->nr_evtchns--;
	rb_erase(&evtchn->node, &u->evtchns);
	kfree(evtchn);
}