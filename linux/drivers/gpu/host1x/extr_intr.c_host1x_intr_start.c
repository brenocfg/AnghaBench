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
typedef  int /*<<< orphan*/  u32 ;
struct host1x {int /*<<< orphan*/  intr_mutex; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int host1x_hw_intr_init_host_sync (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syncpt_thresh_work ; 

void host1x_intr_start(struct host1x *host)
{
	u32 hz = clk_get_rate(host->clk);
	int err;

	mutex_lock(&host->intr_mutex);
	err = host1x_hw_intr_init_host_sync(host, DIV_ROUND_UP(hz, 1000000),
					    syncpt_thresh_work);
	if (err) {
		mutex_unlock(&host->intr_mutex);
		return;
	}
	mutex_unlock(&host->intr_mutex);
}