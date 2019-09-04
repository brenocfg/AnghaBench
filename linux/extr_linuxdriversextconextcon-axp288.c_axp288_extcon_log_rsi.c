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
struct axp288_extcon_info {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_PS_BOOT_REASON_REG ; 
 unsigned int BIT (unsigned int) ; 
 char** axp288_pwr_up_down_info ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const* const) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void axp288_extcon_log_rsi(struct axp288_extcon_info *info)
{
	const char * const *rsi;
	unsigned int val, i, clear_mask = 0;
	int ret;

	ret = regmap_read(info->regmap, AXP288_PS_BOOT_REASON_REG, &val);
	for (i = 0, rsi = axp288_pwr_up_down_info; *rsi; rsi++, i++) {
		if (val & BIT(i)) {
			dev_dbg(info->dev, "%s\n", *rsi);
			clear_mask |= BIT(i);
		}
	}

	/* Clear the register value for next reboot (write 1 to clear bit) */
	regmap_write(info->regmap, AXP288_PS_BOOT_REASON_REG, clear_mask);
}