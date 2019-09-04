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

/* Variables and functions */
 int /*<<< orphan*/  MADERA_BOOT_DONE_EINT1 ; 
 unsigned int MADERA_BOOT_DONE_STS1 ; 
 int /*<<< orphan*/  MADERA_BOOT_POLL_MAX_INTERVAL_US ; 
 int /*<<< orphan*/  MADERA_BOOT_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  MADERA_IRQ1_RAW_STATUS_1 ; 
 int /*<<< orphan*/  MADERA_IRQ1_STATUS_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madera_wait_for_boot(struct madera *madera)
{
	unsigned int val;
	int ret;

	/*
	 * We can't use an interrupt as we need to runtime resume to do so,
	 * so we poll the status bit. This won't race with the interrupt
	 * handler because it will be blocked on runtime resume.
	 */
	ret = regmap_read_poll_timeout(madera->regmap,
				       MADERA_IRQ1_RAW_STATUS_1,
				       val,
				       (val & MADERA_BOOT_DONE_STS1),
				       MADERA_BOOT_POLL_MAX_INTERVAL_US,
				       MADERA_BOOT_POLL_TIMEOUT_US);

	if (ret)
		dev_err(madera->dev, "Polling BOOT_DONE_STS failed: %d\n", ret);

	/*
	 * BOOT_DONE defaults to unmasked on boot so we must ack it.
	 * Do this unconditionally to avoid interrupt storms.
	 */
	regmap_write(madera->regmap, MADERA_IRQ1_STATUS_1,
		     MADERA_BOOT_DONE_EINT1);

	pm_runtime_mark_last_busy(madera->dev);

	return ret;
}