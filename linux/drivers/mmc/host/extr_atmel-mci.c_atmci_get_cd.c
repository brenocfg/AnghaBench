#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmc_host {int /*<<< orphan*/  class_dev; } ;
struct atmel_mci_slot {int detect_is_active_high; int /*<<< orphan*/  detect_pin; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct atmel_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int atmci_get_cd(struct mmc_host *mmc)
{
	int			present = -ENOSYS;
	struct atmel_mci_slot	*slot = mmc_priv(mmc);

	if (gpio_is_valid(slot->detect_pin)) {
		present = !(gpio_get_value(slot->detect_pin) ^
			    slot->detect_is_active_high);
		dev_dbg(&mmc->class_dev, "card is %spresent\n",
				present ? "" : "not ");
	}

	return present;
}