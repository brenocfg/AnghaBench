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
struct mddev {scalar_t__ curr_resync; unsigned long curr_mark_cnt; unsigned long resync_mark; unsigned long resync_mark_cnt; int /*<<< orphan*/  recovery_active; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
sync_speed_show(struct mddev *mddev, char *page)
{
	unsigned long resync, dt, db;
	if (mddev->curr_resync == 0)
		return sprintf(page, "none\n");
	resync = mddev->curr_mark_cnt - atomic_read(&mddev->recovery_active);
	dt = (jiffies - mddev->resync_mark) / HZ;
	if (!dt) dt++;
	db = resync - mddev->resync_mark_cnt;
	return sprintf(page, "%lu\n", db/dt/2); /* K/sec */
}