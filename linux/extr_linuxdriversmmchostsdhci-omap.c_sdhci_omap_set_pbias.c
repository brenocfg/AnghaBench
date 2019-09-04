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
struct sdhci_omap_host {int pbias_enabled; int /*<<< orphan*/  pbias; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int sdhci_omap_set_pbias(struct sdhci_omap_host *omap_host,
				bool power_on, unsigned int iov)
{
	int ret;
	struct device *dev = omap_host->dev;

	if (IS_ERR(omap_host->pbias))
		return 0;

	if (power_on) {
		ret = regulator_set_voltage(omap_host->pbias, iov, iov);
		if (ret) {
			dev_err(dev, "pbias set voltage failed\n");
			return ret;
		}

		if (omap_host->pbias_enabled)
			return 0;

		ret = regulator_enable(omap_host->pbias);
		if (ret) {
			dev_err(dev, "pbias reg enable fail\n");
			return ret;
		}

		omap_host->pbias_enabled = true;
	} else {
		if (!omap_host->pbias_enabled)
			return 0;

		ret = regulator_disable(omap_host->pbias);
		if (ret) {
			dev_err(dev, "pbias reg disable fail\n");
			return ret;
		}
		omap_host->pbias_enabled = false;
	}

	return 0;
}