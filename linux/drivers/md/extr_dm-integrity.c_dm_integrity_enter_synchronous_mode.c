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
struct dm_integrity_c {char mode; int synchronous_mode; int /*<<< orphan*/  commit_wq; int /*<<< orphan*/  bitmap_flush_work; scalar_t__ bitmap_flush_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_print (char*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_integrity_enter_synchronous_mode(struct dm_integrity_c *ic)
{
	DEBUG_print("dm_integrity_enter_synchronous_mode\n");

	if (ic->mode == 'B') {
		ic->bitmap_flush_interval = msecs_to_jiffies(10) + 1;
		ic->synchronous_mode = 1;

		cancel_delayed_work_sync(&ic->bitmap_flush_work);
		queue_delayed_work(ic->commit_wq, &ic->bitmap_flush_work, 0);
		flush_workqueue(ic->commit_wq);
	}
}