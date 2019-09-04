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
struct ssp_data {int /*<<< orphan*/  work_refresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

int ssp_queue_ssp_refresh_task(struct ssp_data *data, unsigned int delay)
{
	cancel_delayed_work_sync(&data->work_refresh);

	return queue_delayed_work(system_power_efficient_wq,
				  &data->work_refresh,
				  msecs_to_jiffies(delay));
}