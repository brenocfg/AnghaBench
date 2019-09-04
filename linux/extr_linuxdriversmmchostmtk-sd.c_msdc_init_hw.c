#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {void* pad_tune; void* iocon; } ;
struct TYPE_5__ {void* pad_tune; void* iocon; } ;
struct msdc_host {int base; int /*<<< orphan*/  dev; TYPE_3__ saved_tune_para; TYPE_2__ def_tune_para; TYPE_1__* dev_comp; } ;
struct TYPE_4__ {int pad_tune_reg; scalar_t__ data_tune; scalar_t__ support_64g; scalar_t__ enhance_rx; scalar_t__ async_fifo; scalar_t__ busy_check; scalar_t__ stop_clk_fix; } ;

/* Variables and functions */
 int EMMC50_CFG0 ; 
 int EMMC50_CFG_CFCSTS_SEL ; 
 int MSDC_CFG ; 
 int MSDC_CFG_CKPDN ; 
 int MSDC_CFG_MODE ; 
 int /*<<< orphan*/  MSDC_CKGEN_MSDC_DLY_SEL ; 
 int MSDC_INT ; 
 int MSDC_INTEN ; 
 int MSDC_IOCON ; 
 int /*<<< orphan*/  MSDC_IOCON_DDLSEL ; 
 int MSDC_PAD_TUNE_CMD_SEL ; 
 int MSDC_PAD_TUNE_RD_SEL ; 
 int MSDC_PAD_TUNE_RXDLYSEL ; 
 int MSDC_PATCH_BIT ; 
 int MSDC_PATCH_BIT1 ; 
 int /*<<< orphan*/  MSDC_PATCH_BIT1_STOP_DLY ; 
 int MSDC_PATCH_BIT2 ; 
 int MSDC_PATCH_BIT2_CFGCRCSTS ; 
 int MSDC_PATCH_BIT2_CFGRESP ; 
 int /*<<< orphan*/  MSDC_PB2_CRCSTSENSEL ; 
 int /*<<< orphan*/  MSDC_PB2_RESPSTSENSEL ; 
 int /*<<< orphan*/  MSDC_PB2_RESPWAIT ; 
 int MSDC_PB2_SUPPORT_64G ; 
 int MSDC_PS ; 
 int MSDC_PS_CDEN ; 
 int SDC_ADV_CFG0 ; 
 int SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_DTOC ; 
 int SDC_CFG_SDIO ; 
 int SDC_CFG_SDIOIDE ; 
 int SDC_FIFO_CFG ; 
 int SDC_FIFO_CFG_RDVALIDSEL ; 
 int SDC_FIFO_CFG_WRVALIDSEL ; 
 int SDC_RX_ENHANCE_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 
 void* readl (int) ; 
 int /*<<< orphan*/  sdr_clr_bits (int,int) ; 
 int /*<<< orphan*/  sdr_set_bits (int,int) ; 
 int /*<<< orphan*/  sdr_set_field (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void msdc_init_hw(struct msdc_host *host)
{
	u32 val;
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	/* Configure to MMC/SD mode, clock free running */
	sdr_set_bits(host->base + MSDC_CFG, MSDC_CFG_MODE | MSDC_CFG_CKPDN);

	/* Reset */
	msdc_reset_hw(host);

	/* Disable card detection */
	sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);

	/* Disable and clear all interrupts */
	writel(0, host->base + MSDC_INTEN);
	val = readl(host->base + MSDC_INT);
	writel(val, host->base + MSDC_INT);

	writel(0, host->base + tune_reg);
	writel(0, host->base + MSDC_IOCON);
	sdr_set_field(host->base + MSDC_IOCON, MSDC_IOCON_DDLSEL, 0);
	writel(0x403c0046, host->base + MSDC_PATCH_BIT);
	sdr_set_field(host->base + MSDC_PATCH_BIT, MSDC_CKGEN_MSDC_DLY_SEL, 1);
	writel(0xffff4089, host->base + MSDC_PATCH_BIT1);
	sdr_set_bits(host->base + EMMC50_CFG0, EMMC50_CFG_CFCSTS_SEL);

	if (host->dev_comp->stop_clk_fix) {
		sdr_set_field(host->base + MSDC_PATCH_BIT1,
			      MSDC_PATCH_BIT1_STOP_DLY, 3);
		sdr_clr_bits(host->base + SDC_FIFO_CFG,
			     SDC_FIFO_CFG_WRVALIDSEL);
		sdr_clr_bits(host->base + SDC_FIFO_CFG,
			     SDC_FIFO_CFG_RDVALIDSEL);
	}

	if (host->dev_comp->busy_check)
		sdr_clr_bits(host->base + MSDC_PATCH_BIT1, (1 << 7));

	if (host->dev_comp->async_fifo) {
		sdr_set_field(host->base + MSDC_PATCH_BIT2,
			      MSDC_PB2_RESPWAIT, 3);
		if (host->dev_comp->enhance_rx) {
			sdr_set_bits(host->base + SDC_ADV_CFG0,
				     SDC_RX_ENHANCE_EN);
		} else {
			sdr_set_field(host->base + MSDC_PATCH_BIT2,
				      MSDC_PB2_RESPSTSENSEL, 2);
			sdr_set_field(host->base + MSDC_PATCH_BIT2,
				      MSDC_PB2_CRCSTSENSEL, 2);
		}
		/* use async fifo, then no need tune internal delay */
		sdr_clr_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PATCH_BIT2_CFGRESP);
		sdr_set_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PATCH_BIT2_CFGCRCSTS);
	}

	if (host->dev_comp->support_64g)
		sdr_set_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PB2_SUPPORT_64G);
	if (host->dev_comp->data_tune) {
		sdr_set_bits(host->base + tune_reg,
			     MSDC_PAD_TUNE_RD_SEL | MSDC_PAD_TUNE_CMD_SEL);
	} else {
		/* choose clock tune */
		sdr_set_bits(host->base + tune_reg, MSDC_PAD_TUNE_RXDLYSEL);
	}

	/* Configure to enable SDIO mode.
	 * it's must otherwise sdio cmd5 failed
	 */
	sdr_set_bits(host->base + SDC_CFG, SDC_CFG_SDIO);

	/* disable detect SDIO device interrupt function */
	sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);

	/* Configure to default data timeout */
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC, 3);

	host->def_tune_para.iocon = readl(host->base + MSDC_IOCON);
	host->def_tune_para.pad_tune = readl(host->base + tune_reg);
	host->saved_tune_para.iocon = readl(host->base + MSDC_IOCON);
	host->saved_tune_para.pad_tune = readl(host->base + tune_reg);
	dev_dbg(host->dev, "init hardware done!");
}