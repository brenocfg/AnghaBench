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
struct sm_ftl {int /*<<< orphan*/  flush_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_flush_workqueue ; 
 struct sm_ftl* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sm_ftl* ftl ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void sm_cache_flush_timer(struct timer_list *t)
{
	struct sm_ftl *ftl = from_timer(ftl, t, timer);
	queue_work(cache_flush_workqueue, &ftl->flush_work);
}