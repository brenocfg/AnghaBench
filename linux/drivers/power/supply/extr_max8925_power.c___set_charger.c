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
struct max8925_power_info {int /*<<< orphan*/  (* set_charger ) (int) ;int /*<<< orphan*/  gpm; struct max8925_chip* chip; } ;
struct max8925_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8925_CHG_CNTL1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  max8925_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static int __set_charger(struct max8925_power_info *info, int enable)
{
	struct max8925_chip *chip = info->chip;
	if (enable) {
		/* enable charger in platform */
		if (info->set_charger)
			info->set_charger(1);
		/* enable charger */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 0);
	} else {
		/* disable charge */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 1 << 7);
		if (info->set_charger)
			info->set_charger(0);
	}
	dev_dbg(chip->dev, "%s\n", (enable) ? "Enable charger"
		: "Disable charger");
	return 0;
}