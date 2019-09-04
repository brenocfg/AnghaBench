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
struct atmel_mci_slot {int /*<<< orphan*/  wp_pin; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct atmel_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int atmci_get_ro(struct mmc_host *mmc)
{
	int			read_only = -ENOSYS;
	struct atmel_mci_slot	*slot = mmc_priv(mmc);

	if (gpio_is_valid(slot->wp_pin)) {
		read_only = gpio_get_value(slot->wp_pin);
		dev_dbg(&mmc->class_dev, "card is %s\n",
				read_only ? "read-only" : "read-write");
	}

	return read_only;
}