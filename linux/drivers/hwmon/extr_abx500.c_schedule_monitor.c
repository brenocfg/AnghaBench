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
struct abx500_temp {int work_active; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MONITOR_DELAY ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void schedule_monitor(struct abx500_temp *data)
{
	data->work_active = true;
	schedule_delayed_work(&data->work, DEFAULT_MONITOR_DELAY);
}