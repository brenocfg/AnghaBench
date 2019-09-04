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
typedef  int u32 ;
struct TYPE_3__ {int bus_width; } ;
struct mmc_host {int caps; TYPE_1__ ios; } ;
struct TYPE_4__ {int /*<<< orphan*/  generic_cmd6_time; } ;
struct mmc_card {int mmc_avail_type; TYPE_2__ ext_csd; struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_BUS_WIDTH ; 
 int EXT_CSD_CARD_TYPE_DDR_1_2V ; 
 int EXT_CSD_CARD_TYPE_DDR_1_8V ; 
 int EXT_CSD_CARD_TYPE_DDR_52 ; 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int EXT_CSD_DDR_BUS_WIDTH_4 ; 
 int EXT_CSD_DDR_BUS_WIDTH_8 ; 
 int MMC_BUS_WIDTH_1 ; 
 int MMC_BUS_WIDTH_8 ; 
 int MMC_CAP_1_8V_DDR ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_120 ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_180 ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_330 ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_DDR52 ; 
 int __mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int mmc_set_signal_voltage (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_select_hs_ddr(struct mmc_card *card)
{
	struct mmc_host *host = card->host;
	u32 bus_width, ext_csd_bits;
	int err = 0;

	if (!(card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_52))
		return 0;

	bus_width = host->ios.bus_width;
	if (bus_width == MMC_BUS_WIDTH_1)
		return 0;

	ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
		EXT_CSD_DDR_BUS_WIDTH_8 : EXT_CSD_DDR_BUS_WIDTH_4;

	err = __mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_BUS_WIDTH,
			   ext_csd_bits,
			   card->ext_csd.generic_cmd6_time,
			   MMC_TIMING_MMC_DDR52,
			   true, true, true);
	if (err) {
		pr_err("%s: switch to bus width %d ddr failed\n",
			mmc_hostname(host), 1 << bus_width);
		return err;
	}

	/*
	 * eMMC cards can support 3.3V to 1.2V i/o (vccq)
	 * signaling.
	 *
	 * EXT_CSD_CARD_TYPE_DDR_1_8V means 3.3V or 1.8V vccq.
	 *
	 * 1.8V vccq at 3.3V core voltage (vcc) is not required
	 * in the JEDEC spec for DDR.
	 *
	 * Even (e)MMC card can support 3.3v to 1.2v vccq, but not all
	 * host controller can support this, like some of the SDHCI
	 * controller which connect to an eMMC device. Some of these
	 * host controller still needs to use 1.8v vccq for supporting
	 * DDR mode.
	 *
	 * So the sequence will be:
	 * if (host and device can both support 1.2v IO)
	 *	use 1.2v IO;
	 * else if (host and device can both support 1.8v IO)
	 *	use 1.8v IO;
	 * so if host and device can only support 3.3v IO, this is the
	 * last choice.
	 *
	 * WARNING: eMMC rules are NOT the same as SD DDR
	 */
	if (card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_1_2V) {
		err = mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_120);
		if (!err)
			return 0;
	}

	if (card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_1_8V &&
	    host->caps & MMC_CAP_1_8V_DDR)
		err = mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_180);

	/* make sure vccq is 3.3v after switching disaster */
	if (err)
		err = mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_330);

	return err;
}