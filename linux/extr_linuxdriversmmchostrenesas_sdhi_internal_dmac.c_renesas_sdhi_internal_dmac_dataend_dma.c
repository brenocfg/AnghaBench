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
struct tmio_mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_complete; } ;
struct renesas_sdhi {TYPE_1__ dma_priv; } ;

/* Variables and functions */
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
renesas_sdhi_internal_dmac_dataend_dma(struct tmio_mmc_host *host) {
	struct renesas_sdhi *priv = host_to_priv(host);

	tasklet_schedule(&priv->dma_priv.dma_complete);
}