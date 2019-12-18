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
struct mmc_host {int dummy; } ;
struct gb_sdio_host {int read_only; int /*<<< orphan*/  lock; scalar_t__ removed; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 struct gb_sdio_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_mmc_get_ro(struct mmc_host *mmc)
{
	struct gb_sdio_host *host = mmc_priv(mmc);

	mutex_lock(&host->lock);
	if (host->removed) {
		mutex_unlock(&host->lock);
		return -ESHUTDOWN;
	}
	mutex_unlock(&host->lock);

	return host->read_only;
}