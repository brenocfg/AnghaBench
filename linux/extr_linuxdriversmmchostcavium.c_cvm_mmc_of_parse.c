#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {int ocr_avail; int caps; size_t f_max; int f_min; TYPE_1__ supply; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct cvm_mmc_slot {size_t cmd_cnt; size_t dat_cnt; TYPE_2__* host; struct mmc_host* mmc; } ;
struct TYPE_4__ {unsigned long long sys_freq; scalar_t__* slot; } ;

/* Variables and functions */
 size_t CAVIUM_MAX_MMC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 

__attribute__((used)) static int cvm_mmc_of_parse(struct device *dev, struct cvm_mmc_slot *slot)
{
	u32 id, cmd_skew = 0, dat_skew = 0, bus_width = 0;
	struct device_node *node = dev->of_node;
	struct mmc_host *mmc = slot->mmc;
	u64 clock_period;
	int ret;

	ret = of_property_read_u32(node, "reg", &id);
	if (ret) {
		dev_err(dev, "Missing or invalid reg property on %pOF\n", node);
		return ret;
	}

	if (id >= CAVIUM_MAX_MMC || slot->host->slot[id]) {
		dev_err(dev, "Invalid reg property on %pOF\n", node);
		return -EINVAL;
	}

	ret = mmc_regulator_get_supply(mmc);
	if (ret)
		return ret;
	/*
	 * Legacy Octeon firmware has no regulator entry, fall-back to
	 * a hard-coded voltage to get a sane OCR.
	 */
	if (IS_ERR(mmc->supply.vmmc))
		mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	/* Common MMC bindings */
	ret = mmc_of_parse(mmc);
	if (ret)
		return ret;

	/* Set bus width */
	if (!(mmc->caps & (MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA))) {
		of_property_read_u32(node, "cavium,bus-max-width", &bus_width);
		if (bus_width == 8)
			mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
		else if (bus_width == 4)
			mmc->caps |= MMC_CAP_4_BIT_DATA;
	}

	/* Set maximum and minimum frequency */
	if (!mmc->f_max)
		of_property_read_u32(node, "spi-max-frequency", &mmc->f_max);
	if (!mmc->f_max || mmc->f_max > 52000000)
		mmc->f_max = 52000000;
	mmc->f_min = 400000;

	/* Sampling register settings, period in picoseconds */
	clock_period = 1000000000000ull / slot->host->sys_freq;
	of_property_read_u32(node, "cavium,cmd-clk-skew", &cmd_skew);
	of_property_read_u32(node, "cavium,dat-clk-skew", &dat_skew);
	slot->cmd_cnt = (cmd_skew + clock_period / 2) / clock_period;
	slot->dat_cnt = (dat_skew + clock_period / 2) / clock_period;

	return id;
}