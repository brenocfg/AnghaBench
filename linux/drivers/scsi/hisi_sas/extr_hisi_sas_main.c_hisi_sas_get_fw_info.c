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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hisi_hba {int refclk_frequency_mhz; int /*<<< orphan*/  queue_count; int /*<<< orphan*/  n_phy; int /*<<< orphan*/  ctrl_clock_ena_reg; int /*<<< orphan*/  ctrl_reset_sts_reg; int /*<<< orphan*/  ctrl_reset_reg; struct clk* ctrl; int /*<<< orphan*/  sas_addr; struct platform_device* platform_dev; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_property_read_u8_array (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct clk* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

int hisi_sas_get_fw_info(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	struct platform_device *pdev = hisi_hba->platform_dev;
	struct device_node *np = pdev ? pdev->dev.of_node : NULL;
	struct clk *refclk;

	if (device_property_read_u8_array(dev, "sas-addr", hisi_hba->sas_addr,
					  SAS_ADDR_SIZE)) {
		dev_err(dev, "could not get property sas-addr\n");
		return -ENOENT;
	}

	if (np) {
		/*
		 * These properties are only required for platform device-based
		 * controller with DT firmware.
		 */
		hisi_hba->ctrl = syscon_regmap_lookup_by_phandle(np,
					"hisilicon,sas-syscon");
		if (IS_ERR(hisi_hba->ctrl)) {
			dev_err(dev, "could not get syscon\n");
			return -ENOENT;
		}

		if (device_property_read_u32(dev, "ctrl-reset-reg",
					     &hisi_hba->ctrl_reset_reg)) {
			dev_err(dev, "could not get property ctrl-reset-reg\n");
			return -ENOENT;
		}

		if (device_property_read_u32(dev, "ctrl-reset-sts-reg",
					     &hisi_hba->ctrl_reset_sts_reg)) {
			dev_err(dev, "could not get property ctrl-reset-sts-reg\n");
			return -ENOENT;
		}

		if (device_property_read_u32(dev, "ctrl-clock-ena-reg",
					     &hisi_hba->ctrl_clock_ena_reg)) {
			dev_err(dev, "could not get property ctrl-clock-ena-reg\n");
			return -ENOENT;
		}
	}

	refclk = devm_clk_get(dev, NULL);
	if (IS_ERR(refclk))
		dev_dbg(dev, "no ref clk property\n");
	else
		hisi_hba->refclk_frequency_mhz = clk_get_rate(refclk) / 1000000;

	if (device_property_read_u32(dev, "phy-count", &hisi_hba->n_phy)) {
		dev_err(dev, "could not get property phy-count\n");
		return -ENOENT;
	}

	if (device_property_read_u32(dev, "queue-count",
				     &hisi_hba->queue_count)) {
		dev_err(dev, "could not get property queue-count\n");
		return -ENOENT;
	}

	return 0;
}