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
struct TYPE_2__ {unsigned int generic_cmd6_time; unsigned int power_off_longtime; int /*<<< orphan*/  power_off_notification; } ;
struct mmc_card {TYPE_1__ ext_csd; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int /*<<< orphan*/  EXT_CSD_NO_POWER_NOTIFICATION ; 
 unsigned int EXT_CSD_POWER_OFF_LONG ; 
 int /*<<< orphan*/  EXT_CSD_POWER_OFF_NOTIFICATION ; 
 int __mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mmc_poweroff_notify(struct mmc_card *card, unsigned int notify_type)
{
	unsigned int timeout = card->ext_csd.generic_cmd6_time;
	int err;

	/* Use EXT_CSD_POWER_OFF_SHORT as default notification type. */
	if (notify_type == EXT_CSD_POWER_OFF_LONG)
		timeout = card->ext_csd.power_off_longtime;

	err = __mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
			EXT_CSD_POWER_OFF_NOTIFICATION,
			notify_type, timeout, 0, true, false, false);
	if (err)
		pr_err("%s: Power Off Notification timed out, %u\n",
		       mmc_hostname(card->host), timeout);

	/* Disable the power off notification after the switch operation. */
	card->ext_csd.power_off_notification = EXT_CSD_NO_POWER_NOTIFICATION;

	return err;
}