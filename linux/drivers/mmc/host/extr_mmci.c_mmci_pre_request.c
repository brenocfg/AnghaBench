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
struct mmci_host {int dummy; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int /*<<< orphan*/  host_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmci_prep_data (struct mmci_host*,struct mmc_data*,int) ; 
 scalar_t__ mmci_validate_data (struct mmci_host*,struct mmc_data*) ; 

__attribute__((used)) static void mmci_pre_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mmci_host *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (!data)
		return;

	WARN_ON(data->host_cookie);

	if (mmci_validate_data(host, data))
		return;

	mmci_prep_data(host, data, true);
}