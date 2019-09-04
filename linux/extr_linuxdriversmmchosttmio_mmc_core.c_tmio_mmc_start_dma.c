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
struct tmio_mmc_host {TYPE_1__* dma_ops; } ;
struct mmc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (struct tmio_mmc_host*,struct mmc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tmio_mmc_host*,struct mmc_data*) ; 

__attribute__((used)) static inline void tmio_mmc_start_dma(struct tmio_mmc_host *host,
				      struct mmc_data *data)
{
	if (host->dma_ops)
		host->dma_ops->start(host, data);
}