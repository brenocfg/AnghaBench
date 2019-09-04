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
struct mmci_platform_data {unsigned int (* status ) (int /*<<< orphan*/ ) ;} ;
struct mmci_host {int /*<<< orphan*/  mmc; struct mmci_platform_data* plat; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 unsigned int ENOSYS ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 unsigned int mmc_gpio_get_cd (struct mmc_host*) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmci_get_cd(struct mmc_host *mmc)
{
	struct mmci_host *host = mmc_priv(mmc);
	struct mmci_platform_data *plat = host->plat;
	unsigned int status = mmc_gpio_get_cd(mmc);

	if (status == -ENOSYS) {
		if (!plat->status)
			return 1; /* Assume always present */

		status = plat->status(mmc_dev(host->mmc));
	}
	return status;
}