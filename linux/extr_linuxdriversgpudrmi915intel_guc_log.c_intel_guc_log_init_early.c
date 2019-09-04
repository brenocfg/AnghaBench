#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  lock; } ;
struct intel_guc_log {TYPE_1__ relay; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capture_logs_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void intel_guc_log_init_early(struct intel_guc_log *log)
{
	mutex_init(&log->relay.lock);
	INIT_WORK(&log->relay.flush_work, capture_logs_work);
}