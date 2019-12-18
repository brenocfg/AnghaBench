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
struct wbsd_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  mrq; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbsd_finish_data (struct wbsd_host*,struct mmc_data*) ; 
 struct mmc_data* wbsd_get_data (struct wbsd_host*) ; 

__attribute__((used)) static void wbsd_tasklet_finish(unsigned long param)
{
	struct wbsd_host *host = (struct wbsd_host *)param;
	struct mmc_data *data;

	spin_lock(&host->lock);

	WARN_ON(!host->mrq);
	if (!host->mrq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	wbsd_finish_data(host, data);

end:
	spin_unlock(&host->lock);
}