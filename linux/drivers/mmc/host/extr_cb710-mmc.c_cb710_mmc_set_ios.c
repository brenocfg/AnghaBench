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
struct mmc_ios {scalar_t__ power_mode; scalar_t__ bus_width; int /*<<< orphan*/  clock; } ;
struct mmc_host {int dummy; } ;
struct cb710_slot {int dummy; } ;
struct cb710_mmc_reader {scalar_t__ last_power_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_IE_TEST_MASK ; 
 scalar_t__ MMC_BUS_WIDTH_1 ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  cb710_mmc_enable_4bit_data (struct cb710_slot*,int) ; 
 int /*<<< orphan*/  cb710_mmc_enable_irq (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_mmc_powerdown (struct cb710_slot*) ; 
 int cb710_mmc_powerup (struct cb710_slot*) ; 
 int /*<<< orphan*/  cb710_mmc_select_clock_divider (struct mmc_host*,int /*<<< orphan*/ ) ; 
 struct cb710_slot* cb710_mmc_to_slot (struct mmc_host*) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct cb710_mmc_reader* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cb710_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct cb710_slot *slot = cb710_mmc_to_slot(mmc);
	struct cb710_mmc_reader *reader = mmc_priv(mmc);
	int err;

	cb710_mmc_select_clock_divider(mmc, ios->clock);

	if (ios->power_mode != reader->last_power_mode) {
		switch (ios->power_mode) {
		case MMC_POWER_ON:
			err = cb710_mmc_powerup(slot);
			if (err) {
				dev_warn(cb710_slot_dev(slot),
					"powerup failed (%d)- retrying\n", err);
				cb710_mmc_powerdown(slot);
				udelay(1);
				err = cb710_mmc_powerup(slot);
				if (err)
					dev_warn(cb710_slot_dev(slot),
						"powerup retry failed (%d) - expect errors\n",
					err);
			}
			reader->last_power_mode = MMC_POWER_ON;
			break;
		case MMC_POWER_OFF:
			cb710_mmc_powerdown(slot);
			reader->last_power_mode = MMC_POWER_OFF;
			break;
		case MMC_POWER_UP:
		default:
			/* ignore */
			break;
		}
	}

	cb710_mmc_enable_4bit_data(slot, ios->bus_width != MMC_BUS_WIDTH_1);

	cb710_mmc_enable_irq(slot, CB710_MMC_IE_TEST_MASK, 0);
}