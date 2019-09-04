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
struct tmio_mmc_host {int /*<<< orphan*/  chan_rx; int /*<<< orphan*/  chan_tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct tmio_mmc_host*,int) ;} ;
struct renesas_sdhi {TYPE_1__ dma_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CM_INFO1 ; 
 int /*<<< orphan*/  INFO1_CLEAR ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_dm_write (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tmio_mmc_host*,int) ; 

__attribute__((used)) static void
renesas_sdhi_internal_dmac_enable_dma(struct tmio_mmc_host *host, bool enable)
{
	struct renesas_sdhi *priv = host_to_priv(host);

	if (!host->chan_tx || !host->chan_rx)
		return;

	if (!enable)
		renesas_sdhi_internal_dmac_dm_write(host, DM_CM_INFO1,
						    INFO1_CLEAR);

	if (priv->dma_priv.enable)
		priv->dma_priv.enable(host, enable);
}