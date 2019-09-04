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
struct dm_writecache {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  writeback_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  autocommit_timer ; 
 struct dm_writecache* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dm_writecache* wc ; 
 int /*<<< orphan*/  writecache_has_error (struct dm_writecache*) ; 

__attribute__((used)) static void writecache_autocommit_timer(struct timer_list *t)
{
	struct dm_writecache *wc = from_timer(wc, t, autocommit_timer);
	if (!writecache_has_error(wc))
		queue_work(wc->writeback_wq, &wc->flush_work);
}