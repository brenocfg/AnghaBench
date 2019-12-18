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
struct watchdog_device {int dummy; } ;
struct uniphier_wdt_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDTCTRL ; 
 int /*<<< orphan*/  WDTCTRL_CLEAR ; 
 unsigned int WDTCTRL_STATUS ; 
 int /*<<< orphan*/  WDTST_TIMEOUT ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uniphier_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int uniphier_watchdog_ping(struct watchdog_device *w)
{
	struct uniphier_wdt_dev *wdev = watchdog_get_drvdata(w);
	unsigned int val;
	int ret;

	/* Clear counter */
	ret = regmap_write_bits(wdev->regmap, WDTCTRL,
				WDTCTRL_CLEAR, WDTCTRL_CLEAR);
	if (!ret)
		/*
		 * As SoC specification, after clear counter,
		 * it needs to wait until counter status is 1.
		 */
		ret = regmap_read_poll_timeout(wdev->regmap, WDTCTRL, val,
					       (val & WDTCTRL_STATUS),
					       0, WDTST_TIMEOUT);

	return ret;
}