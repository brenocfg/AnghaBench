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
struct tmio_mmc_host {int /*<<< orphan*/ * chan_rx; int /*<<< orphan*/ * chan_tx; TYPE_1__* dma_ops; } ;
struct tmio_mmc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* request ) (struct tmio_mmc_host*,struct tmio_mmc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tmio_mmc_host*,struct tmio_mmc_data*) ; 

__attribute__((used)) static inline void tmio_mmc_request_dma(struct tmio_mmc_host *host,
					struct tmio_mmc_data *pdata)
{
	if (host->dma_ops) {
		host->dma_ops->request(host, pdata);
	} else {
		host->chan_tx = NULL;
		host->chan_rx = NULL;
	}
}