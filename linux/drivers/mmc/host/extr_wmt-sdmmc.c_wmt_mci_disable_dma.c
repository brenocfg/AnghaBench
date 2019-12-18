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
struct wmt_mci_priv {scalar_t__ sdmmc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ISR_INT_STS ; 
 scalar_t__ SDDMA_IER ; 
 scalar_t__ SDDMA_ISR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wmt_mci_disable_dma(struct wmt_mci_priv *priv)
{
	writel(DMA_ISR_INT_STS, priv->sdmmc_base + SDDMA_ISR);
	writel(0, priv->sdmmc_base + SDDMA_IER);
}