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
struct TYPE_2__ {int sd3_bus_mode; } ;
struct mmc_card {TYPE_1__ sw_caps; } ;

/* Variables and functions */
 int SD_MODE_UHS_DDR50 ; 
 int SD_MODE_UHS_SDR104 ; 
 int SD_MODE_UHS_SDR50 ; 

__attribute__((used)) static bool mmc_sd_card_using_v18(struct mmc_card *card)
{
	/*
	 * According to the SD spec., the Bus Speed Mode (function group 1) bits
	 * 2 to 4 are zero if the card is initialized at 3.3V signal level. Thus
	 * they can be used to determine if the card has already switched to
	 * 1.8V signaling.
	 */
	return card->sw_caps.sd3_bus_mode &
	       (SD_MODE_UHS_SDR50 | SD_MODE_UHS_SDR104 | SD_MODE_UHS_DDR50);
}