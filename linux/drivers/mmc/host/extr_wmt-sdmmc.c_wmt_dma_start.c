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
typedef  int u32 ;
struct wmt_mci_priv {scalar_t__ sdmmc_base; } ;

/* Variables and functions */
 int DMA_CCR_RUN ; 
 scalar_t__ SDDMA_CCR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void wmt_dma_start(struct wmt_mci_priv *priv)
{
	u32 reg_tmp;

	reg_tmp = readl(priv->sdmmc_base + SDDMA_CCR);
	writel(reg_tmp | DMA_CCR_RUN, priv->sdmmc_base + SDDMA_CCR);
}