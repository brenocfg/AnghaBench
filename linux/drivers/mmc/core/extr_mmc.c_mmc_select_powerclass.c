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
struct TYPE_2__ {int bus_width; } ;
struct mmc_host {TYPE_1__ ios; } ;
struct mmc_card {int mmc_avail_type; struct mmc_host* host; } ;

/* Variables and functions */
 int EXT_CSD_BUS_WIDTH_4 ; 
 int EXT_CSD_BUS_WIDTH_8 ; 
 int EXT_CSD_CARD_TYPE_DDR_52 ; 
 int EXT_CSD_DDR_BUS_WIDTH_4 ; 
 int EXT_CSD_DDR_BUS_WIDTH_8 ; 
 int MMC_BUS_WIDTH_1 ; 
 int MMC_BUS_WIDTH_8 ; 
 int __mmc_select_powerclass (struct mmc_card*,int) ; 
 int /*<<< orphan*/  mmc_can_ext_csd (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mmc_select_powerclass(struct mmc_card *card)
{
	struct mmc_host *host = card->host;
	u32 bus_width, ext_csd_bits;
	int err, ddr;

	/* Power class selection is supported for versions >= 4.0 */
	if (!mmc_can_ext_csd(card))
		return 0;

	bus_width = host->ios.bus_width;
	/* Power class values are defined only for 4/8 bit bus */
	if (bus_width == MMC_BUS_WIDTH_1)
		return 0;

	ddr = card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_52;
	if (ddr)
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_DDR_BUS_WIDTH_8 : EXT_CSD_DDR_BUS_WIDTH_4;
	else
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_BUS_WIDTH_8 :  EXT_CSD_BUS_WIDTH_4;

	err = __mmc_select_powerclass(card, ext_csd_bits);
	if (err)
		pr_warn("%s: power class selection to bus width %d ddr %d failed\n",
			mmc_hostname(host), 1 << bus_width, ddr);

	return err;
}