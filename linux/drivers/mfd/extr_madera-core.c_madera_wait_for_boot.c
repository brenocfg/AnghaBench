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
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MADERA_BOOT_DONE_EINT1 ; 
 unsigned int MADERA_BOOT_DONE_STS1 ; 
 int MADERA_BOOT_POLL_INTERVAL_USEC ; 
 int /*<<< orphan*/  MADERA_BOOT_POLL_TIMEOUT_USEC ; 
 int /*<<< orphan*/  MADERA_IRQ1_RAW_STATUS_1 ; 
 int /*<<< orphan*/  MADERA_IRQ1_STATUS_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int madera_wait_for_boot(struct madera *madera)
{
	ktime_t timeout;
	unsigned int val = 0;
	int ret = 0;

	/*
	 * We can't use an interrupt as we need to runtime resume to do so,
	 * so we poll the status bit. This won't race with the interrupt
	 * handler because it will be blocked on runtime resume.
	 * The chip could NAK a read request while it is booting so ignore
	 * errors from regmap_read.
	 */
	timeout = ktime_add_us(ktime_get(), MADERA_BOOT_POLL_TIMEOUT_USEC);
	regmap_read(madera->regmap, MADERA_IRQ1_RAW_STATUS_1, &val);
	while (!(val & MADERA_BOOT_DONE_STS1) &&
	       !ktime_after(ktime_get(), timeout)) {
		usleep_range(MADERA_BOOT_POLL_INTERVAL_USEC / 2,
			     MADERA_BOOT_POLL_INTERVAL_USEC);
		regmap_read(madera->regmap, MADERA_IRQ1_RAW_STATUS_1, &val);
	}

	if (!(val & MADERA_BOOT_DONE_STS1)) {
		dev_err(madera->dev, "Polling BOOT_DONE_STS timed out\n");
		ret = -ETIMEDOUT;
	}

	/*
	 * BOOT_DONE defaults to unmasked on boot so we must ack it.
	 * Do this even after a timeout to avoid interrupt storms.
	 */
	regmap_write(madera->regmap, MADERA_IRQ1_STATUS_1,
		     MADERA_BOOT_DONE_EINT1);

	pm_runtime_mark_last_busy(madera->dev);

	return ret;
}