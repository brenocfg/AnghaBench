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
struct dw_mci_slot {int id; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRTPRT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int mci_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_gpio_get_ro (struct mmc_host*) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int dw_mci_get_ro(struct mmc_host *mmc)
{
	int read_only;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	int gpio_ro = mmc_gpio_get_ro(mmc);

	/* Use platform get_ro function, else try on board write protect */
	if (gpio_ro >= 0)
		read_only = gpio_ro;
	else
		read_only =
			mci_readl(slot->host, WRTPRT) & (1 << slot->id) ? 1 : 0;

	dev_dbg(&mmc->class_dev, "card is %s\n",
		read_only ? "read-only" : "read-write");

	return read_only;
}