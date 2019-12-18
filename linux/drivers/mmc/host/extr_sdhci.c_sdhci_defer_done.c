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
struct sdhci_host {int flags; scalar_t__ pending_reset; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_data {scalar_t__ host_cookie; } ;

/* Variables and functions */
 scalar_t__ COOKIE_MAPPED ; 
 int SDHCI_REQ_USE_DMA ; 

__attribute__((used)) static inline bool sdhci_defer_done(struct sdhci_host *host,
				    struct mmc_request *mrq)
{
	struct mmc_data *data = mrq->data;

	return host->pending_reset ||
	       ((host->flags & SDHCI_REQ_USE_DMA) && data &&
		data->host_cookie == COOKIE_MAPPED);
}