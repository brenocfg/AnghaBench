#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pad_type; int /*<<< orphan*/  reg; int /*<<< orphan*/  set_soc_pad; } ;
struct xenon_emmc_phy_params {TYPE_1__ pad_ctrl; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct resource {int dummy; } ;
typedef  char const device_node ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC_PAD_FIXED_1_8V ; 
 int /*<<< orphan*/  SOC_PAD_SD ; 
 int /*<<< orphan*/  armada_3700_soc_pad_voltage_set ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ of_address_to_resource (char const*,int,struct resource*) ; 
 scalar_t__ of_device_is_compatible (char const*,char*) ; 
 int of_property_read_string (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int get_dt_pad_ctrl_data(struct sdhci_host *host,
				struct device_node *np,
				struct xenon_emmc_phy_params *params)
{
	int ret = 0;
	const char *name;
	struct resource iomem;

	if (of_device_is_compatible(np, "marvell,armada-3700-sdhci"))
		params->pad_ctrl.set_soc_pad = armada_3700_soc_pad_voltage_set;
	else
		return 0;

	if (of_address_to_resource(np, 1, &iomem)) {
		dev_err(mmc_dev(host->mmc), "Unable to find SoC PAD ctrl register address for %pOFn\n",
			np);
		return -EINVAL;
	}

	params->pad_ctrl.reg = devm_ioremap_resource(mmc_dev(host->mmc),
						     &iomem);
	if (IS_ERR(params->pad_ctrl.reg))
		return PTR_ERR(params->pad_ctrl.reg);

	ret = of_property_read_string(np, "marvell,pad-type", &name);
	if (ret) {
		dev_err(mmc_dev(host->mmc), "Unable to determine SoC PHY PAD ctrl type\n");
		return ret;
	}
	if (!strcmp(name, "sd")) {
		params->pad_ctrl.pad_type = SOC_PAD_SD;
	} else if (!strcmp(name, "fixed-1-8v")) {
		params->pad_ctrl.pad_type = SOC_PAD_FIXED_1_8V;
	} else {
		dev_err(mmc_dev(host->mmc), "Unsupported SoC PHY PAD ctrl type %s\n",
			name);
		return -EINVAL;
	}

	return ret;
}