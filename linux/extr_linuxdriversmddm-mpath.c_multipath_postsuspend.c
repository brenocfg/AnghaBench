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
struct multipath {int /*<<< orphan*/  work_mutex; } ;
struct dm_target {struct multipath* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_multipath_work (struct multipath*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multipath_postsuspend(struct dm_target *ti)
{
	struct multipath *m = ti->private;

	mutex_lock(&m->work_mutex);
	flush_multipath_work(m);
	mutex_unlock(&m->work_mutex);
}