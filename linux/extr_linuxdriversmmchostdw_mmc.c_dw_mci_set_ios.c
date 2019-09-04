#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_ios {int bus_width; scalar_t__ timing; scalar_t__ clock; int power_mode; int /*<<< orphan*/  vdd; } ;
struct TYPE_6__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct dw_mci_slot {int id; scalar_t__ clock; TYPE_2__* host; int /*<<< orphan*/  flags; int /*<<< orphan*/  ctype; } ;
struct dw_mci_drv_data {int /*<<< orphan*/  (* set_ios ) (TYPE_2__*,struct mmc_ios*) ;} ;
struct TYPE_7__ {scalar_t__ timing; int vqmmc_enabled; scalar_t__ state; int /*<<< orphan*/  dev; struct dw_mci_drv_data* drv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_MMC_CARD_NEED_INIT ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_BUS_WIDTH_4 132 
#define  MMC_BUS_WIDTH_8 131 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  PWREN ; 
 int /*<<< orphan*/  SDMMC_CTRL_ALL_RESET_FLAGS ; 
 int /*<<< orphan*/  SDMMC_CTYPE_1BIT ; 
 int /*<<< orphan*/  SDMMC_CTYPE_4BIT ; 
 int /*<<< orphan*/  SDMMC_CTYPE_8BIT ; 
 scalar_t__ STATE_IDLE ; 
 scalar_t__ STATE_WAITING_CMD11_DONE ; 
 int /*<<< orphan*/  UHS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_mci_ctrl_reset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mci_setup_bus (struct dw_mci_slot*,int) ; 
 int mci_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct mmc_ios*) ; 

__attribute__((used)) static void dw_mci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	const struct dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 regs;
	int ret;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_4:
		slot->ctype = SDMMC_CTYPE_4BIT;
		break;
	case MMC_BUS_WIDTH_8:
		slot->ctype = SDMMC_CTYPE_8BIT;
		break;
	default:
		/* set default 1 bit mode */
		slot->ctype = SDMMC_CTYPE_1BIT;
	}

	regs = mci_readl(slot->host, UHS_REG);

	/* DDR mode set */
	if (ios->timing == MMC_TIMING_MMC_DDR52 ||
	    ios->timing == MMC_TIMING_UHS_DDR50 ||
	    ios->timing == MMC_TIMING_MMC_HS400)
		regs |= ((0x1 << slot->id) << 16);
	else
		regs &= ~((0x1 << slot->id) << 16);

	mci_writel(slot->host, UHS_REG, regs);
	slot->host->timing = ios->timing;

	/*
	 * Use mirror of ios->clock to prevent race with mmc
	 * core ios update when finding the minimum.
	 */
	slot->clock = ios->clock;

	if (drv_data && drv_data->set_ios)
		drv_data->set_ios(slot->host, ios);

	switch (ios->power_mode) {
	case MMC_POWER_UP:
		if (!IS_ERR(mmc->supply.vmmc)) {
			ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
					ios->vdd);
			if (ret) {
				dev_err(slot->host->dev,
					"failed to enable vmmc regulator\n");
				/*return, if failed turn on vmmc*/
				return;
			}
		}
		set_bit(DW_MMC_CARD_NEED_INIT, &slot->flags);
		regs = mci_readl(slot->host, PWREN);
		regs |= (1 << slot->id);
		mci_writel(slot->host, PWREN, regs);
		break;
	case MMC_POWER_ON:
		if (!slot->host->vqmmc_enabled) {
			if (!IS_ERR(mmc->supply.vqmmc)) {
				ret = regulator_enable(mmc->supply.vqmmc);
				if (ret < 0)
					dev_err(slot->host->dev,
						"failed to enable vqmmc\n");
				else
					slot->host->vqmmc_enabled = true;

			} else {
				/* Keep track so we don't reset again */
				slot->host->vqmmc_enabled = true;
			}

			/* Reset our state machine after powering on */
			dw_mci_ctrl_reset(slot->host,
					  SDMMC_CTRL_ALL_RESET_FLAGS);
		}

		/* Adjust clock / bus width after power is up */
		dw_mci_setup_bus(slot, false);

		break;
	case MMC_POWER_OFF:
		/* Turn clock off before power goes down */
		dw_mci_setup_bus(slot, false);

		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		if (!IS_ERR(mmc->supply.vqmmc) && slot->host->vqmmc_enabled)
			regulator_disable(mmc->supply.vqmmc);
		slot->host->vqmmc_enabled = false;

		regs = mci_readl(slot->host, PWREN);
		regs &= ~(1 << slot->id);
		mci_writel(slot->host, PWREN, regs);
		break;
	default:
		break;
	}

	if (slot->host->state == STATE_WAITING_CMD11_DONE && ios->clock != 0)
		slot->host->state = STATE_IDLE;
}