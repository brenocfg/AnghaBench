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
struct mmc_host {int caps; } ;
struct TYPE_2__ {int /*<<< orphan*/  generic_cmd6_time; } ;
struct mmc_card {TYPE_1__ ext_csd; struct mmc_host* host; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  EXT_CSD_BUS_WIDTH ; 
#define  EXT_CSD_BUS_WIDTH_4 131 
#define  EXT_CSD_BUS_WIDTH_8 130 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
#define  MMC_BUS_WIDTH_4 129 
#define  MMC_BUS_WIDTH_8 128 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_BUS_WIDTH_TEST ; 
 int mmc_bus_test (struct mmc_card*,unsigned int) ; 
 int /*<<< orphan*/  mmc_can_ext_csd (struct mmc_card*) ; 
 int mmc_compare_ext_csds (struct mmc_card*,unsigned int) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_bus_width (struct mmc_host*,unsigned int) ; 
 int mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_select_bus_width(struct mmc_card *card)
{
	static unsigned ext_csd_bits[] = {
		EXT_CSD_BUS_WIDTH_8,
		EXT_CSD_BUS_WIDTH_4,
	};
	static unsigned bus_widths[] = {
		MMC_BUS_WIDTH_8,
		MMC_BUS_WIDTH_4,
	};
	struct mmc_host *host = card->host;
	unsigned idx, bus_width = 0;
	int err = 0;

	if (!mmc_can_ext_csd(card) ||
	    !(host->caps & (MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA)))
		return 0;

	idx = (host->caps & MMC_CAP_8_BIT_DATA) ? 0 : 1;

	/*
	 * Unlike SD, MMC cards dont have a configuration register to notify
	 * supported bus width. So bus test command should be run to identify
	 * the supported bus width or compare the ext csd values of current
	 * bus width and ext csd values of 1 bit mode read earlier.
	 */
	for (; idx < ARRAY_SIZE(bus_widths); idx++) {
		/*
		 * Host is capable of 8bit transfer, then switch
		 * the device to work in 8bit transfer mode. If the
		 * mmc switch command returns error then switch to
		 * 4bit transfer mode. On success set the corresponding
		 * bus width on the host.
		 */
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_BUS_WIDTH,
				 ext_csd_bits[idx],
				 card->ext_csd.generic_cmd6_time);
		if (err)
			continue;

		bus_width = bus_widths[idx];
		mmc_set_bus_width(host, bus_width);

		/*
		 * If controller can't handle bus width test,
		 * compare ext_csd previously read in 1 bit mode
		 * against ext_csd at new bus width
		 */
		if (!(host->caps & MMC_CAP_BUS_WIDTH_TEST))
			err = mmc_compare_ext_csds(card, bus_width);
		else
			err = mmc_bus_test(card, bus_width);

		if (!err) {
			err = bus_width;
			break;
		} else {
			pr_warn("%s: switch to bus width %d failed\n",
				mmc_hostname(host), 1 << bus_width);
		}
	}

	return err;
}