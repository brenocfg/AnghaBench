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
struct wbsd_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  mrq; } ;
struct mmc_data {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGF (char*) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct mmc_data* wbsd_get_data (struct wbsd_host*) ; 

__attribute__((used)) static void wbsd_tasklet_timeout(unsigned long param)
{
	struct wbsd_host *host = (struct wbsd_host *)param;
	struct mmc_data *data;

	spin_lock(&host->lock);

	if (!host->mrq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	DBGF("Timeout\n");

	data->error = -ETIMEDOUT;

	tasklet_schedule(&host->finish_tasklet);

end:
	spin_unlock(&host->lock);
}