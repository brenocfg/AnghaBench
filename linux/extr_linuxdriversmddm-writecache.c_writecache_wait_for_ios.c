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
struct dm_writecache {int /*<<< orphan*/ * bio_in_progress; int /*<<< orphan*/ * bio_in_progress_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void writecache_wait_for_ios(struct dm_writecache *wc, int direction)
{
	wait_event(wc->bio_in_progress_wait[direction],
		   !atomic_read(&wc->bio_in_progress[direction]));
}