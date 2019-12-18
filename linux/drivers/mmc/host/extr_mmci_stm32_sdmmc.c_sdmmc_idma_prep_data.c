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
struct mmci_host {scalar_t__ next_cookie; } ;
struct mmc_data {scalar_t__ host_cookie; } ;

/* Variables and functions */
 int _sdmmc_idma_prep_data (struct mmci_host*,struct mmc_data*) ; 

__attribute__((used)) static int sdmmc_idma_prep_data(struct mmci_host *host,
				struct mmc_data *data, bool next)
{
	/* Check if job is already prepared. */
	if (!next && data->host_cookie == host->next_cookie)
		return 0;

	return _sdmmc_idma_prep_data(host, data);
}