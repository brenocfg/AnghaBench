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
struct dw_mci {int dma_64bit_address; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMOD ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  PLDMND ; 
 int /*<<< orphan*/  SDMMC_CTRL_DMA_RESET ; 
 int SDMMC_CTRL_USE_IDMAC ; 
 int SDMMC_IDMAC_ENABLE ; 
 int SDMMC_IDMAC_FB ; 
 int /*<<< orphan*/  dw_mci_ctrl_reset (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mci_idmac_reset (struct dw_mci*) ; 
 int dw_mci_prepare_desc32 (struct dw_mci*,int /*<<< orphan*/ ,unsigned int) ; 
 int dw_mci_prepare_desc64 (struct dw_mci*,int /*<<< orphan*/ ,unsigned int) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int dw_mci_idmac_start_dma(struct dw_mci *host, unsigned int sg_len)
{
	u32 temp;
	int ret;

	if (host->dma_64bit_address == 1)
		ret = dw_mci_prepare_desc64(host, host->data, sg_len);
	else
		ret = dw_mci_prepare_desc32(host, host->data, sg_len);

	if (ret)
		goto out;

	/* drain writebuffer */
	wmb();

	/* Make sure to reset DMA in case we did PIO before this */
	dw_mci_ctrl_reset(host, SDMMC_CTRL_DMA_RESET);
	dw_mci_idmac_reset(host);

	/* Select IDMAC interface */
	temp = mci_readl(host, CTRL);
	temp |= SDMMC_CTRL_USE_IDMAC;
	mci_writel(host, CTRL, temp);

	/* drain writebuffer */
	wmb();

	/* Enable the IDMAC */
	temp = mci_readl(host, BMOD);
	temp |= SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB;
	mci_writel(host, BMOD, temp);

	/* Start it running */
	mci_writel(host, PLDMND, 1);

out:
	return ret;
}