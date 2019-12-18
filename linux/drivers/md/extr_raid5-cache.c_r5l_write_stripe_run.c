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
struct r5l_log {int /*<<< orphan*/  io_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5l_submit_current_io (struct r5l_log*) ; 

void r5l_write_stripe_run(struct r5l_log *log)
{
	if (!log)
		return;
	mutex_lock(&log->io_mutex);
	r5l_submit_current_io(log);
	mutex_unlock(&log->io_mutex);
}