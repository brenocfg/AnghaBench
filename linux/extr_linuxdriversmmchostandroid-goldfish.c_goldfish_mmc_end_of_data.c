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
struct mmc_data {int dummy; } ;
struct goldfish_mmc_host {scalar_t__ dma_done; int /*<<< orphan*/  dma_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  goldfish_mmc_xfer_done (struct goldfish_mmc_host*,struct mmc_data*) ; 

__attribute__((used)) static void goldfish_mmc_end_of_data(struct goldfish_mmc_host *host,
				     struct mmc_data *data)
{
	if (!host->dma_in_use) {
		goldfish_mmc_xfer_done(host, data);
		return;
	}
	if (host->dma_done)
		goldfish_mmc_xfer_done(host, data);
}