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
struct dm_integrity_c {int /*<<< orphan*/  commit_work; int /*<<< orphan*/  commit_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  autocommit_timer ; 
 int /*<<< orphan*/  dm_integrity_failed (struct dm_integrity_c*) ; 
 struct dm_integrity_c* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct dm_integrity_c* ic ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void autocommit_fn(struct timer_list *t)
{
	struct dm_integrity_c *ic = from_timer(ic, t, autocommit_timer);

	if (likely(!dm_integrity_failed(ic)))
		queue_work(ic->commit_wq, &ic->commit_work);
}