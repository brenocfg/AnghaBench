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
typedef  int u32 ;
struct TYPE_2__ {int sd3_curr_limit; } ;
struct mmc_card {scalar_t__ sd_bus_speed; int /*<<< orphan*/  host; TYPE_1__ sw_caps; } ;

/* Variables and functions */
 int SD_MAX_CURRENT_200 ; 
 int SD_MAX_CURRENT_400 ; 
 int SD_MAX_CURRENT_600 ; 
 int SD_MAX_CURRENT_800 ; 
 int SD_SET_CURRENT_LIMIT_200 ; 
 int SD_SET_CURRENT_LIMIT_400 ; 
 int SD_SET_CURRENT_LIMIT_600 ; 
 int SD_SET_CURRENT_LIMIT_800 ; 
 int SD_SET_CURRENT_NO_CHANGE ; 
 scalar_t__ UHS_DDR50_BUS_SPEED ; 
 scalar_t__ UHS_SDR104_BUS_SPEED ; 
 scalar_t__ UHS_SDR50_BUS_SPEED ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_sd_switch (struct mmc_card*,int,int,int,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int sd_get_host_max_current (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_set_current_limit(struct mmc_card *card, u8 *status)
{
	int current_limit = SD_SET_CURRENT_NO_CHANGE;
	int err;
	u32 max_current;

	/*
	 * Current limit switch is only defined for SDR50, SDR104, and DDR50
	 * bus speed modes. For other bus speed modes, we do not change the
	 * current limit.
	 */
	if ((card->sd_bus_speed != UHS_SDR50_BUS_SPEED) &&
	    (card->sd_bus_speed != UHS_SDR104_BUS_SPEED) &&
	    (card->sd_bus_speed != UHS_DDR50_BUS_SPEED))
		return 0;

	/*
	 * Host has different current capabilities when operating at
	 * different voltages, so find out its max current first.
	 */
	max_current = sd_get_host_max_current(card->host);

	/*
	 * We only check host's capability here, if we set a limit that is
	 * higher than the card's maximum current, the card will be using its
	 * maximum current, e.g. if the card's maximum current is 300ma, and
	 * when we set current limit to 200ma, the card will draw 200ma, and
	 * when we set current limit to 400/600/800ma, the card will draw its
	 * maximum 300ma from the host.
	 *
	 * The above is incorrect: if we try to set a current limit that is
	 * not supported by the card, the card can rightfully error out the
	 * attempt, and remain at the default current limit.  This results
	 * in a 300mA card being limited to 200mA even though the host
	 * supports 800mA. Failures seen with SanDisk 8GB UHS cards with
	 * an iMX6 host. --rmk
	 */
	if (max_current >= 800 &&
	    card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_800)
		current_limit = SD_SET_CURRENT_LIMIT_800;
	else if (max_current >= 600 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_600)
		current_limit = SD_SET_CURRENT_LIMIT_600;
	else if (max_current >= 400 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_400)
		current_limit = SD_SET_CURRENT_LIMIT_400;
	else if (max_current >= 200 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_200)
		current_limit = SD_SET_CURRENT_LIMIT_200;

	if (current_limit != SD_SET_CURRENT_NO_CHANGE) {
		err = mmc_sd_switch(card, 1, 3, current_limit, status);
		if (err)
			return err;

		if (((status[15] >> 4) & 0x0F) != current_limit)
			pr_warn("%s: Problem setting current limit!\n",
				mmc_hostname(card->host));

	}

	return 0;
}