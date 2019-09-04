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
typedef  int u32 ;
struct dw_mci_slot {unsigned int clock; unsigned int __clk_old; int id; int ctype; TYPE_1__* mmc; int /*<<< orphan*/  flags; struct dw_mci* host; } ;
struct dw_mci {scalar_t__ state; unsigned int current_speed; unsigned int bus_hz; } ;
struct TYPE_2__ {int actual_clock; int caps; unsigned int f_min; int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKDIV ; 
 int /*<<< orphan*/  CLKENA ; 
 int /*<<< orphan*/  CLKSRC ; 
 int /*<<< orphan*/  CTYPE ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DW_MMC_CARD_NEEDS_POLL ; 
 int /*<<< orphan*/  DW_MMC_CARD_NO_LOW_PWR ; 
 int MMC_CAP_NEEDS_POLL ; 
 int SDMMC_CLKEN_ENABLE ; 
 int SDMMC_CLKEN_LOW_PWR ; 
 int SDMMC_CMD_PRV_DAT_WAIT ; 
 int SDMMC_CMD_UPD_CLK ; 
 int SDMMC_CMD_VOLT_SWITCH ; 
 scalar_t__ STATE_WAITING_CMD11_DONE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  mci_send_cmd (struct dw_mci_slot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_mci_setup_bus(struct dw_mci_slot *slot, bool force_clkinit)
{
	struct dw_mci *host = slot->host;
	unsigned int clock = slot->clock;
	u32 div;
	u32 clk_en_a;
	u32 sdmmc_cmd_bits = SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT;

	/* We must continue to set bit 28 in CMD until the change is complete */
	if (host->state == STATE_WAITING_CMD11_DONE)
		sdmmc_cmd_bits |= SDMMC_CMD_VOLT_SWITCH;

	slot->mmc->actual_clock = 0;

	if (!clock) {
		mci_writel(host, CLKENA, 0);
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);
	} else if (clock != host->current_speed || force_clkinit) {
		div = host->bus_hz / clock;
		if (host->bus_hz % clock && host->bus_hz > clock)
			/*
			 * move the + 1 after the divide to prevent
			 * over-clocking the card.
			 */
			div += 1;

		div = (host->bus_hz != clock) ? DIV_ROUND_UP(div, 2) : 0;

		if ((clock != slot->__clk_old &&
			!test_bit(DW_MMC_CARD_NEEDS_POLL, &slot->flags)) ||
			force_clkinit) {
			/* Silent the verbose log if calling from PM context */
			if (!force_clkinit)
				dev_info(&slot->mmc->class_dev,
					 "Bus speed (slot %d) = %dHz (slot req %dHz, actual %dHZ div = %d)\n",
					 slot->id, host->bus_hz, clock,
					 div ? ((host->bus_hz / div) >> 1) :
					 host->bus_hz, div);

			/*
			 * If card is polling, display the message only
			 * one time at boot time.
			 */
			if (slot->mmc->caps & MMC_CAP_NEEDS_POLL &&
					slot->mmc->f_min == clock)
				set_bit(DW_MMC_CARD_NEEDS_POLL, &slot->flags);
		}

		/* disable clock */
		mci_writel(host, CLKENA, 0);
		mci_writel(host, CLKSRC, 0);

		/* inform CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* set clock to desired speed */
		mci_writel(host, CLKDIV, div);

		/* inform CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* enable clock; only low power if no SDIO */
		clk_en_a = SDMMC_CLKEN_ENABLE << slot->id;
		if (!test_bit(DW_MMC_CARD_NO_LOW_PWR, &slot->flags))
			clk_en_a |= SDMMC_CLKEN_LOW_PWR << slot->id;
		mci_writel(host, CLKENA, clk_en_a);

		/* inform CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* keep the last clock value that was requested from core */
		slot->__clk_old = clock;
		slot->mmc->actual_clock = div ? ((host->bus_hz / div) >> 1) :
					  host->bus_hz;
	}

	host->current_speed = clock;

	/* Set the current slot bus width */
	mci_writel(host, CTYPE, (slot->ctype << slot->id));
}