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
struct smbb_charger {int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_CTL_EN ; 
 scalar_t__ SMBB_USB_OTG_CTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct smbb_charger* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smbb_chg_otg_disable(struct regulator_dev *rdev)
{
	struct smbb_charger *chg = rdev_get_drvdata(rdev);
	int rc;

	rc = regmap_update_bits(chg->regmap, chg->addr + SMBB_USB_OTG_CTL,
				OTG_CTL_EN, 0);
	if (rc)
		dev_err(chg->dev, "failed to update OTG_CTL\n");
	return rc;
}