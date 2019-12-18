#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct mmc_card {int type; size_t sd_bus_speed; TYPE_1__ dev; int /*<<< orphan*/  host; int /*<<< orphan*/  rca; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
#define  MMC_TYPE_MMC 136 
#define  MMC_TYPE_SD 135 
#define  MMC_TYPE_SDIO 134 
#define  MMC_TYPE_SD_COMBO 133 
#define  UHS_DDR50_BUS_SPEED 132 
#define  UHS_SDR104_BUS_SPEED 131 
#define  UHS_SDR12_BUS_SPEED 130 
#define  UHS_SDR25_BUS_SPEED 129 
#define  UHS_SDR50_BUS_SPEED 128 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_add_card_debugfs (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_blockaddr (struct mmc_card*) ; 
 scalar_t__ mmc_card_ddr52 (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_ext_capacity (struct mmc_card*) ; 
 scalar_t__ mmc_card_hs (struct mmc_card*) ; 
 scalar_t__ mmc_card_hs200 (struct mmc_card*) ; 
 scalar_t__ mmc_card_hs400 (struct mmc_card*) ; 
 scalar_t__ mmc_card_hs400es (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_set_present (struct mmc_card*) ; 
 scalar_t__ mmc_card_uhs (struct mmc_card*) ; 
 scalar_t__ mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_of_find_child_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,char*,char const*,...) ; 

int mmc_add_card(struct mmc_card *card)
{
	int ret;
	const char *type;
	const char *uhs_bus_speed_mode = "";
	static const char *const uhs_speeds[] = {
		[UHS_SDR12_BUS_SPEED] = "SDR12 ",
		[UHS_SDR25_BUS_SPEED] = "SDR25 ",
		[UHS_SDR50_BUS_SPEED] = "SDR50 ",
		[UHS_SDR104_BUS_SPEED] = "SDR104 ",
		[UHS_DDR50_BUS_SPEED] = "DDR50 ",
	};


	dev_set_name(&card->dev, "%s:%04x", mmc_hostname(card->host), card->rca);

	switch (card->type) {
	case MMC_TYPE_MMC:
		type = "MMC";
		break;
	case MMC_TYPE_SD:
		type = "SD";
		if (mmc_card_blockaddr(card)) {
			if (mmc_card_ext_capacity(card))
				type = "SDXC";
			else
				type = "SDHC";
		}
		break;
	case MMC_TYPE_SDIO:
		type = "SDIO";
		break;
	case MMC_TYPE_SD_COMBO:
		type = "SD-combo";
		if (mmc_card_blockaddr(card))
			type = "SDHC-combo";
		break;
	default:
		type = "?";
		break;
	}

	if (mmc_card_uhs(card) &&
		(card->sd_bus_speed < ARRAY_SIZE(uhs_speeds)))
		uhs_bus_speed_mode = uhs_speeds[card->sd_bus_speed];

	if (mmc_host_is_spi(card->host)) {
		pr_info("%s: new %s%s%s card on SPI\n",
			mmc_hostname(card->host),
			mmc_card_hs(card) ? "high speed " : "",
			mmc_card_ddr52(card) ? "DDR " : "",
			type);
	} else {
		pr_info("%s: new %s%s%s%s%s%s card at address %04x\n",
			mmc_hostname(card->host),
			mmc_card_uhs(card) ? "ultra high speed " :
			(mmc_card_hs(card) ? "high speed " : ""),
			mmc_card_hs400(card) ? "HS400 " :
			(mmc_card_hs200(card) ? "HS200 " : ""),
			mmc_card_hs400es(card) ? "Enhanced strobe " : "",
			mmc_card_ddr52(card) ? "DDR " : "",
			uhs_bus_speed_mode, type, card->rca);
	}

#ifdef CONFIG_DEBUG_FS
	mmc_add_card_debugfs(card);
#endif
	card->dev.of_node = mmc_of_find_child_device(card->host, 0);

	device_enable_async_suspend(&card->dev);

	ret = device_add(&card->dev);
	if (ret)
		return ret;

	mmc_card_set_present(card);

	return 0;
}