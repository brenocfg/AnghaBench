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
struct mmci_host {scalar_t__ next_cookie; TYPE_1__* ops; } ;
struct mmc_data {int host_cookie; } ;
struct TYPE_2__ {int (* prep_data ) (struct mmci_host*,struct mmc_data*,int) ;} ;

/* Variables and functions */
 int stub1 (struct mmci_host*,struct mmc_data*,int) ; 

int mmci_prep_data(struct mmci_host *host, struct mmc_data *data, bool next)
{
	int err;

	if (!host->ops || !host->ops->prep_data)
		return 0;

	err = host->ops->prep_data(host, data, next);

	if (next && !err)
		data->host_cookie = ++host->next_cookie < 0 ?
			1 : host->next_cookie;

	return err;
}