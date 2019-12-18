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
struct mmc_data {scalar_t__ host_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_next_data ) (struct mmci_host*,struct mmc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct mmci_host*,struct mmc_data*) ; 

void mmci_get_next_data(struct mmci_host *host, struct mmc_data *data)
{
	WARN_ON(data->host_cookie && data->host_cookie != host->next_cookie);

	if (host->ops && host->ops->get_next_data)
		host->ops->get_next_data(host, data);
}