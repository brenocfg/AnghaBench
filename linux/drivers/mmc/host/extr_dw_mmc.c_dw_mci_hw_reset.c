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
struct mmc_host {int dummy; } ;
struct dw_mci_slot {int id; struct dw_mci* host; } ;
struct dw_mci {scalar_t__ use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  RST_N ; 
 int SDMMC_CTRL_DMA_RESET ; 
 int SDMMC_CTRL_FIFO_RESET ; 
 int SDMMC_RST_HWACTIVE ; 
 scalar_t__ TRANS_MODE_IDMAC ; 
 int /*<<< orphan*/  dw_mci_ctrl_reset (struct dw_mci*,int) ; 
 int /*<<< orphan*/  dw_mci_idmac_reset (struct dw_mci*) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dw_mci_hw_reset(struct mmc_host *mmc)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	int reset;

	if (host->use_dma == TRANS_MODE_IDMAC)
		dw_mci_idmac_reset(host);

	if (!dw_mci_ctrl_reset(host, SDMMC_CTRL_DMA_RESET |
				     SDMMC_CTRL_FIFO_RESET))
		return;

	/*
	 * According to eMMC spec, card reset procedure:
	 * tRstW >= 1us:   RST_n pulse width
	 * tRSCA >= 200us: RST_n to Command time
	 * tRSTH >= 1us:   RST_n high period
	 */
	reset = mci_readl(host, RST_N);
	reset &= ~(SDMMC_RST_HWACTIVE << slot->id);
	mci_writel(host, RST_N, reset);
	usleep_range(1, 2);
	reset |= SDMMC_RST_HWACTIVE << slot->id;
	mci_writel(host, RST_N, reset);
	usleep_range(200, 300);
}