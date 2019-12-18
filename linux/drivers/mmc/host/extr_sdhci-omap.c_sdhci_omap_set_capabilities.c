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
struct sdhci_omap_host {struct device* dev; } ;
struct regulator {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CAPA_VS18 ; 
 int CAPA_VS30 ; 
 int CAPA_VS33 ; 
 int /*<<< orphan*/  IOV_1V8 ; 
 int /*<<< orphan*/  IOV_3V3 ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  SDHCI_OMAP_CAPA ; 
 struct regulator* regulator_get (struct device*,char*) ; 
 scalar_t__ regulator_is_supported_voltage (struct regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 
 int sdhci_omap_readl (struct sdhci_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_omap_writel (struct sdhci_omap_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdhci_omap_set_capabilities(struct sdhci_omap_host *omap_host)
{
	u32 reg;
	int ret = 0;
	struct device *dev = omap_host->dev;
	struct regulator *vqmmc;

	vqmmc = regulator_get(dev, "vqmmc");
	if (IS_ERR(vqmmc)) {
		ret = PTR_ERR(vqmmc);
		goto reg_put;
	}

	/* voltage capabilities might be set by boot loader, clear it */
	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CAPA);
	reg &= ~(CAPA_VS18 | CAPA_VS30 | CAPA_VS33);

	if (regulator_is_supported_voltage(vqmmc, IOV_3V3, IOV_3V3))
		reg |= CAPA_VS33;
	if (regulator_is_supported_voltage(vqmmc, IOV_1V8, IOV_1V8))
		reg |= CAPA_VS18;

	sdhci_omap_writel(omap_host, SDHCI_OMAP_CAPA, reg);

reg_put:
	regulator_put(vqmmc);

	return ret;
}