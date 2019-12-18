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
struct uniphier_sd_priv {int /*<<< orphan*/  chan; } ;
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static void uniphier_sd_external_dma_issue(unsigned long arg)
{
	struct tmio_mmc_host *host = (void *)arg;
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);

	uniphier_sd_dma_endisable(host, 1);
	dma_async_issue_pending(priv->chan);
}