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
struct mmci_host {TYPE_1__* ops; } ;
struct mmc_data {scalar_t__ host_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unprep_data ) (struct mmci_host*,struct mmc_data*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mmci_host*,struct mmc_data*,int) ; 

void mmci_unprep_data(struct mmci_host *host, struct mmc_data *data,
		      int err)
{
	if (host->ops && host->ops->unprep_data)
		host->ops->unprep_data(host, data, err);

	data->host_cookie = 0;
}