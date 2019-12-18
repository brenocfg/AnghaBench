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
struct uniphier_sd_priv {int /*<<< orphan*/  dma_dir; } ;
struct tmio_mmc_host {int /*<<< orphan*/  sg_ptr; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_do_data_irq (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static void uniphier_sd_internal_dma_dataend(struct tmio_mmc_host *host)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);

	uniphier_sd_dma_endisable(host, 0);
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptr, 1, priv->dma_dir);

	tmio_mmc_do_data_irq(host);
}