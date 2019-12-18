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
typedef  int u8 ;
typedef  int u32 ;
struct wmt_mci_priv {scalar_t__ sdmmc_base; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int CTLR_FIFO_RESET ; 
 scalar_t__ SDMMC_ARG ; 
 scalar_t__ SDMMC_CMD ; 
 scalar_t__ SDMMC_CTLR ; 
 scalar_t__ SDMMC_RSPTYPE ; 
 scalar_t__ SDMMC_STS0 ; 
 scalar_t__ SDMMC_STS1 ; 
 scalar_t__ SDMMC_STS2 ; 
 scalar_t__ SDMMC_STS3 ; 
 int /*<<< orphan*/  WMT_SD_POWER_ON ; 
 struct wmt_mci_priv* mmc_priv (struct mmc_host*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  wmt_set_sd_power (struct wmt_mci_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int wmt_mci_send_command(struct mmc_host *mmc, u8 command, u8 cmdtype,
				u32 arg, u8 rsptype)
{
	struct wmt_mci_priv *priv;
	u32 reg_tmp;

	priv = mmc_priv(mmc);

	/* write command, arg, resptype registers */
	writeb(command, priv->sdmmc_base + SDMMC_CMD);
	writel(arg, priv->sdmmc_base + SDMMC_ARG);
	writeb(rsptype, priv->sdmmc_base + SDMMC_RSPTYPE);

	/* reset response FIFO */
	reg_tmp = readb(priv->sdmmc_base + SDMMC_CTLR);
	writeb(reg_tmp | CTLR_FIFO_RESET, priv->sdmmc_base + SDMMC_CTLR);

	/* ensure clock enabled - VT3465 */
	wmt_set_sd_power(priv, WMT_SD_POWER_ON);

	/* clear status bits */
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS1);
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS2);
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS3);

	/* set command type */
	reg_tmp = readb(priv->sdmmc_base + SDMMC_CTLR);
	writeb((reg_tmp & 0x0F) | (cmdtype << 4),
	       priv->sdmmc_base + SDMMC_CTLR);

	return 0;
}