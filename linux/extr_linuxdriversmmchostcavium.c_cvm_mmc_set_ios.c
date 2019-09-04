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
typedef  int u64 ;
struct mmc_ios {int power_mode; int bus_width; scalar_t__ timing; int clock; int /*<<< orphan*/  vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct cvm_mmc_slot {int clock; int cached_switch; int /*<<< orphan*/  bus_id; struct cvm_mmc_host* host; } ;
struct cvm_mmc_host {int sys_freq; int /*<<< orphan*/  (* release_bus ) (struct cvm_mmc_host*) ;int /*<<< orphan*/  (* set_shared_power ) (struct cvm_mmc_host*,int) ;int /*<<< orphan*/  global_pwr_gpiod; int /*<<< orphan*/  (* acquire_bus ) (struct cvm_mmc_host*) ;} ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIO_EMM_SWITCH_BUS_WIDTH ; 
 int /*<<< orphan*/  MIO_EMM_SWITCH_CLK_HI ; 
 int /*<<< orphan*/  MIO_EMM_SWITCH_CLK_LO ; 
 int /*<<< orphan*/  MIO_EMM_SWITCH_HS_TIMING ; 
 int /*<<< orphan*/  MIO_EMM_SWITCH_POWER_CLASS ; 
#define  MMC_BUS_WIDTH_1 133 
#define  MMC_BUS_WIDTH_4 132 
#define  MMC_BUS_WIDTH_8 131 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_MMC_HS ; 
 int /*<<< orphan*/  cvm_mmc_reset_bus (struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  cvm_mmc_switch_to (struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  do_switch (struct cvm_mmc_host*,int) ; 
 struct cvm_mmc_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bus_id (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wdog (struct cvm_mmc_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  stub3 (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  stub4 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  switch_val_changed (struct cvm_mmc_slot*,int) ; 

__attribute__((used)) static void cvm_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct cvm_mmc_slot *slot = mmc_priv(mmc);
	struct cvm_mmc_host *host = slot->host;
	int clk_period = 0, power_class = 10, bus_width = 0;
	u64 clock, emm_switch;

	host->acquire_bus(host);
	cvm_mmc_switch_to(slot);

	/* Set the power state */
	switch (ios->power_mode) {
	case MMC_POWER_ON:
		break;

	case MMC_POWER_OFF:
		cvm_mmc_reset_bus(slot);
		if (host->global_pwr_gpiod)
			host->set_shared_power(host, 0);
		else if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		break;

	case MMC_POWER_UP:
		if (host->global_pwr_gpiod)
			host->set_shared_power(host, 1);
		else if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		break;
	}

	/* Convert bus width to HW definition */
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_8:
		bus_width = 2;
		break;
	case MMC_BUS_WIDTH_4:
		bus_width = 1;
		break;
	case MMC_BUS_WIDTH_1:
		bus_width = 0;
		break;
	}

	/* DDR is available for 4/8 bit bus width */
	if (ios->bus_width && ios->timing == MMC_TIMING_MMC_DDR52)
		bus_width |= 4;

	/* Change the clock frequency. */
	clock = ios->clock;
	if (clock > 52000000)
		clock = 52000000;
	slot->clock = clock;

	if (clock)
		clk_period = (host->sys_freq + clock - 1) / (2 * clock);

	emm_switch = FIELD_PREP(MIO_EMM_SWITCH_HS_TIMING,
				(ios->timing == MMC_TIMING_MMC_HS)) |
		     FIELD_PREP(MIO_EMM_SWITCH_BUS_WIDTH, bus_width) |
		     FIELD_PREP(MIO_EMM_SWITCH_POWER_CLASS, power_class) |
		     FIELD_PREP(MIO_EMM_SWITCH_CLK_HI, clk_period) |
		     FIELD_PREP(MIO_EMM_SWITCH_CLK_LO, clk_period);
	set_bus_id(&emm_switch, slot->bus_id);

	if (!switch_val_changed(slot, emm_switch))
		goto out;

	set_wdog(slot, 0);
	do_switch(host, emm_switch);
	slot->cached_switch = emm_switch;
out:
	host->release_bus(host);
}