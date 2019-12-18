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
struct mmc_ios {scalar_t__ bus_width; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  dev; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_BUS_WIDTH_4BIT ; 
 int /*<<< orphan*/  AU6601_REG_BUS_CTRL ; 
 scalar_t__ MMC_BUS_WIDTH_1 ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  alcor_write8 (struct alcor_pci_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void alcor_set_bus_width(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);
	struct alcor_pci_priv *priv = host->alcor_pci;

	if (ios->bus_width == MMC_BUS_WIDTH_1) {
		alcor_write8(priv, 0, AU6601_REG_BUS_CTRL);
	} else if (ios->bus_width == MMC_BUS_WIDTH_4) {
		alcor_write8(priv, AU6601_BUS_WIDTH_4BIT,
			      AU6601_REG_BUS_CTRL);
	} else
		dev_err(host->dev, "Unknown BUS mode\n");

}