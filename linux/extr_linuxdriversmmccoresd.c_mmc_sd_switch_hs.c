#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ hs_max_dtr; } ;
struct TYPE_7__ {int cmdclass; } ;
struct TYPE_6__ {scalar_t__ sda_vsn; } ;
struct mmc_card {TYPE_4__* host; TYPE_1__ sw_caps; TYPE_3__ csd; TYPE_2__ scr; } ;
struct TYPE_8__ {int caps; } ;

/* Variables and functions */
 int CCC_SWITCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 scalar_t__ SCR_SPEC_VER_1 ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_4__*) ; 
 int mmc_sd_switch (struct mmc_card*,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

int mmc_sd_switch_hs(struct mmc_card *card)
{
	int err;
	u8 *status;

	if (card->scr.sda_vsn < SCR_SPEC_VER_1)
		return 0;

	if (!(card->csd.cmdclass & CCC_SWITCH))
		return 0;

	if (!(card->host->caps & MMC_CAP_SD_HIGHSPEED))
		return 0;

	if (card->sw_caps.hs_max_dtr == 0)
		return 0;

	status = kmalloc(64, GFP_KERNEL);
	if (!status)
		return -ENOMEM;

	err = mmc_sd_switch(card, 1, 0, 1, status);
	if (err)
		goto out;

	if ((status[16] & 0xF) != 1) {
		pr_warn("%s: Problem switching card into high-speed mode!\n",
			mmc_hostname(card->host));
		err = 0;
	} else {
		err = 1;
	}

out:
	kfree(status);

	return err;
}