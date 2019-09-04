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
struct si476x_core {int rds_drainer_is_working; int /*<<< orphan*/  rds_drainer_status_lock; int /*<<< orphan*/  rds_fifo_drainer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void si476x_core_start_rds_drainer_once(struct si476x_core *core)
{
	mutex_lock(&core->rds_drainer_status_lock);
	if (!core->rds_drainer_is_working) {
		core->rds_drainer_is_working = true;
		schedule_work(&core->rds_fifo_drainer);
	}
	mutex_unlock(&core->rds_drainer_status_lock);
}