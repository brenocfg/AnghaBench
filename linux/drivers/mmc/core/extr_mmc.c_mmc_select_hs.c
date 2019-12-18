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
struct TYPE_2__ {int /*<<< orphan*/  generic_cmd6_time; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int /*<<< orphan*/  EXT_CSD_HS_TIMING ; 
 int /*<<< orphan*/  EXT_CSD_TIMING_HS ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_HS ; 
 int __mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_select_hs(struct mmc_card *card)
{
	int err;

	err = __mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS,
			   card->ext_csd.generic_cmd6_time, MMC_TIMING_MMC_HS,
			   true, true, true);
	if (err)
		pr_warn("%s: switch to high-speed failed, err:%d\n",
			mmc_hostname(card->host), err);

	return err;
}