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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  uhs_max_dtr; } ;
struct mmc_card {int sd_bus_speed; TYPE_1__ sw_caps; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_UHS_DDR50 ; 
 unsigned int MMC_TIMING_UHS_SDR104 ; 
 unsigned int MMC_TIMING_UHS_SDR12 ; 
 unsigned int MMC_TIMING_UHS_SDR25 ; 
 unsigned int MMC_TIMING_UHS_SDR50 ; 
#define  UHS_DDR50_BUS_SPEED 132 
 int /*<<< orphan*/  UHS_DDR50_MAX_DTR ; 
#define  UHS_SDR104_BUS_SPEED 131 
 int /*<<< orphan*/  UHS_SDR104_MAX_DTR ; 
#define  UHS_SDR12_BUS_SPEED 130 
 int /*<<< orphan*/  UHS_SDR12_MAX_DTR ; 
#define  UHS_SDR25_BUS_SPEED 129 
 int /*<<< orphan*/  UHS_SDR25_MAX_DTR ; 
#define  UHS_SDR50_BUS_SPEED 128 
 int /*<<< orphan*/  UHS_SDR50_MAX_DTR ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_sd_switch (struct mmc_card*,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  mmc_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_timing (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_set_bus_speed_mode(struct mmc_card *card, u8 *status)
{
	int err;
	unsigned int timing = 0;

	switch (card->sd_bus_speed) {
	case UHS_SDR104_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR104;
		card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
		break;
	case UHS_DDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_DDR50;
		card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
		break;
	case UHS_SDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR50;
		card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
		break;
	case UHS_SDR25_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR25;
		card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
		break;
	case UHS_SDR12_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR12;
		card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
		break;
	default:
		return 0;
	}

	err = mmc_sd_switch(card, 1, 0, card->sd_bus_speed, status);
	if (err)
		return err;

	if ((status[16] & 0xF) != card->sd_bus_speed)
		pr_warn("%s: Problem setting bus speed mode!\n",
			mmc_hostname(card->host));
	else {
		mmc_set_timing(card->host, timing);
		mmc_set_clock(card->host, card->sw_caps.uhs_max_dtr);
	}

	return 0;
}