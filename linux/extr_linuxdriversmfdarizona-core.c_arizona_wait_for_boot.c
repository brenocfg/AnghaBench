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
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_BOOT_DONE_STS ; 
 int /*<<< orphan*/  ARIZONA_INTERRUPT_RAW_STATUS_5 ; 
 int /*<<< orphan*/  ARIZONA_INTERRUPT_STATUS_5 ; 
 int arizona_poll_reg (struct arizona*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_wait_for_boot(struct arizona *arizona)
{
	int ret;

	/*
	 * We can't use an interrupt as we need to runtime resume to do so,
	 * we won't race with the interrupt handler as it'll be blocked on
	 * runtime resume.
	 */
	ret = arizona_poll_reg(arizona, 30, ARIZONA_INTERRUPT_RAW_STATUS_5,
			       ARIZONA_BOOT_DONE_STS, ARIZONA_BOOT_DONE_STS);

	if (!ret)
		regmap_write(arizona->regmap, ARIZONA_INTERRUPT_STATUS_5,
			     ARIZONA_BOOT_DONE_STS);

	pm_runtime_mark_last_busy(arizona->dev);

	return ret;
}