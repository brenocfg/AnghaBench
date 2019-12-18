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
struct llt_ndlc {int /*<<< orphan*/  sm_work; } ;

/* Variables and functions */
 struct llt_ndlc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct llt_ndlc* ndlc ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_timer ; 

__attribute__((used)) static void ndlc_t1_timeout(struct timer_list *t)
{
	struct llt_ndlc *ndlc = from_timer(ndlc, t, t1_timer);

	pr_debug("\n");

	schedule_work(&ndlc->sm_work);
}