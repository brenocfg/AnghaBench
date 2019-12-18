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
struct mmci_host {TYPE_1__* ops; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int /*<<< orphan*/  blksz; } ;
struct TYPE_2__ {int (* validate_data ) (struct mmci_host*,struct mmc_data*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int stub1 (struct mmci_host*,struct mmc_data*) ; 

__attribute__((used)) static int mmci_validate_data(struct mmci_host *host,
			      struct mmc_data *data)
{
	if (!data)
		return 0;

	if (!is_power_of_2(data->blksz)) {
		dev_err(mmc_dev(host->mmc),
			"unsupported block size (%d bytes)\n", data->blksz);
		return -EINVAL;
	}

	if (host->ops && host->ops->validate_data)
		return host->ops->validate_data(host, data);

	return 0;
}