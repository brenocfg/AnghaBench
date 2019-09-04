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
struct dm_writecache {int /*<<< orphan*/  freelist_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 

__attribute__((used)) static void writecache_wait_on_freelist(struct dm_writecache *wc)
{
	DEFINE_WAIT(wait);

	prepare_to_wait(&wc->freelist_wait, &wait, TASK_UNINTERRUPTIBLE);
	wc_unlock(wc);
	io_schedule();
	finish_wait(&wc->freelist_wait, &wait);
	wc_lock(wc);
}