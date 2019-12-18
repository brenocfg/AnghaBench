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
typedef  int u8 ;
struct regulator_dev {int /*<<< orphan*/  dev; } ;
struct ab3100_regulator {int /*<<< orphan*/  regreg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ab3100_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ab3100_set_voltage_regulator_sel(struct regulator_dev *reg,
					    unsigned selector)
{
	struct ab3100_regulator *abreg = rdev_get_drvdata(reg);
	u8 regval;
	int err;

	err = abx500_get_register_interruptible(abreg->dev, 0,
						abreg->regreg, &regval);
	if (err) {
		dev_warn(&reg->dev,
			 "failed to get regulator register %02x\n",
			 abreg->regreg);
		return err;
	}

	/* The highest three bits control the variable regulators */
	regval &= ~0xE0;
	regval |= (selector << 5);

	err = abx500_set_register_interruptible(abreg->dev, 0,
						abreg->regreg, regval);
	if (err)
		dev_warn(&reg->dev, "failed to set regulator register %02x\n",
			abreg->regreg);

	return err;
}