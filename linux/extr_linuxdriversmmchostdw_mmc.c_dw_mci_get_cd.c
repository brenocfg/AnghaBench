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
struct mmc_host {int caps; int /*<<< orphan*/  class_dev; } ;
struct dw_mci_slot {int id; int /*<<< orphan*/  flags; struct dw_mci* host; } ;
struct dw_mci {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDETECT ; 
 int /*<<< orphan*/  DW_MMC_CARD_PRESENT ; 
 int MMC_CAP_NEEDS_POLL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_card_is_removable (struct mmc_host*) ; 
 int mmc_gpio_get_cd (struct mmc_host*) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_mci_get_cd(struct mmc_host *mmc)
{
	int present;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	int gpio_cd = mmc_gpio_get_cd(mmc);

	/* Use platform get_cd function, else try onboard card detect */
	if (((mmc->caps & MMC_CAP_NEEDS_POLL)
				|| !mmc_card_is_removable(mmc))) {
		present = 1;

		if (!test_bit(DW_MMC_CARD_PRESENT, &slot->flags)) {
			if (mmc->caps & MMC_CAP_NEEDS_POLL) {
				dev_info(&mmc->class_dev,
					"card is polling.\n");
			} else {
				dev_info(&mmc->class_dev,
					"card is non-removable.\n");
			}
			set_bit(DW_MMC_CARD_PRESENT, &slot->flags);
		}

		return present;
	} else if (gpio_cd >= 0)
		present = gpio_cd;
	else
		present = (mci_readl(slot->host, CDETECT) & (1 << slot->id))
			== 0 ? 1 : 0;

	spin_lock_bh(&host->lock);
	if (present && !test_and_set_bit(DW_MMC_CARD_PRESENT, &slot->flags))
		dev_dbg(&mmc->class_dev, "card is present\n");
	else if (!present &&
			!test_and_clear_bit(DW_MMC_CARD_PRESENT, &slot->flags))
		dev_dbg(&mmc->class_dev, "card is not present\n");
	spin_unlock_bh(&host->lock);

	return present;
}