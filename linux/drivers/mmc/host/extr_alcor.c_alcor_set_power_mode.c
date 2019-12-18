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
struct mmc_ios {int power_mode; int /*<<< orphan*/  clock; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  dev; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_ACTIVE_CTRL ; 
 int /*<<< orphan*/  AU6601_CLK_DELAY ; 
 int AU6601_DATA_WRITE ; 
 int /*<<< orphan*/  AU6601_DATA_XFER_CTRL ; 
 int /*<<< orphan*/  AU6601_OPT ; 
 int /*<<< orphan*/  AU6601_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  AU6601_POWER_CONTROL ; 
 int /*<<< orphan*/  AU6601_REG_BUS_CTRL ; 
 int AU6601_SD_CARD ; 
 int /*<<< orphan*/  AU6601_TIME_OUT_CTRL ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  alcor_set_clock (struct alcor_sdmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcor_write8 (struct alcor_pci_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void alcor_set_power_mode(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);
	struct alcor_pci_priv *priv = host->alcor_pci;

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		alcor_set_clock(host, ios->clock);
		/* set all pins to input */
		alcor_write8(priv, 0, AU6601_OUTPUT_ENABLE);
		/* turn of VDD */
		alcor_write8(priv, 0, AU6601_POWER_CONTROL);
		break;
	case MMC_POWER_UP:
		break;
	case MMC_POWER_ON:
		/* This is most trickiest part. The order and timings of
		 * instructions seems to play important role. Any changes may
		 * confuse internal state engine if this HW.
		 * FIXME: If we will ever get access to documentation, then this
		 * part should be reviewed again.
		 */

		/* enable SD card mode */
		alcor_write8(priv, AU6601_SD_CARD,
			      AU6601_ACTIVE_CTRL);
		/* set signal voltage to 3.3V */
		alcor_write8(priv, 0, AU6601_OPT);
		/* no documentation about clk delay, for now just try to mimic
		 * original driver.
		 */
		alcor_write8(priv, 0x20, AU6601_CLK_DELAY);
		/* set BUS width to 1 bit */
		alcor_write8(priv, 0, AU6601_REG_BUS_CTRL);
		/* set CLK first time */
		alcor_set_clock(host, ios->clock);
		/* power on VDD */
		alcor_write8(priv, AU6601_SD_CARD,
			      AU6601_POWER_CONTROL);
		/* wait until the CLK will get stable */
		mdelay(20);
		/* set CLK again, mimic original driver. */
		alcor_set_clock(host, ios->clock);

		/* enable output */
		alcor_write8(priv, AU6601_SD_CARD,
			      AU6601_OUTPUT_ENABLE);
		/* The clk will not work on au6621. We need to trigger data
		 * transfer.
		 */
		alcor_write8(priv, AU6601_DATA_WRITE,
			      AU6601_DATA_XFER_CTRL);
		/* configure timeout. Not clear what exactly it means. */
		alcor_write8(priv, 0x7d, AU6601_TIME_OUT_CTRL);
		mdelay(100);
		break;
	default:
		dev_err(host->dev, "Unknown power parameter\n");
	}
}