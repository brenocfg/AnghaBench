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
struct mmc_host {TYPE_1__* bus_ops; scalar_t__ bus_dead; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int (* hw_reset ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mmc_bus_get (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_bus_put (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mmc_host*) ; 

int mmc_hw_reset(struct mmc_host *host)
{
	int ret;

	if (!host->card)
		return -EINVAL;

	mmc_bus_get(host);
	if (!host->bus_ops || host->bus_dead || !host->bus_ops->hw_reset) {
		mmc_bus_put(host);
		return -EOPNOTSUPP;
	}

	ret = host->bus_ops->hw_reset(host);
	mmc_bus_put(host);

	if (ret)
		pr_warn("%s: tried to HW reset card, got error %d\n",
			mmc_hostname(host), ret);

	return ret;
}