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
struct TYPE_2__ {int sec_feature_support; } ;
struct mmc_card {int quirks; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int EXT_CSD_SEC_GB_CL_EN ; 
 int MMC_QUIRK_TRIM_BROKEN ; 

int mmc_can_trim(struct mmc_card *card)
{
	if ((card->ext_csd.sec_feature_support & EXT_CSD_SEC_GB_CL_EN) &&
	    (!(card->quirks & MMC_QUIRK_TRIM_BROKEN)))
		return 1;
	return 0;
}