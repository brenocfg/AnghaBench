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
struct regulator_dev {int dummy; } ;
struct mc13xxx_regulator_priv {int /*<<< orphan*/  mc13xxx; struct mc13xxx_regulator* mc13xxx_regulators; } ;
struct mc13xxx_regulator {unsigned int vsel_shift; int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
 int mc13xxx_reg_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct mc13xxx_regulator_priv* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int mc13xxx_regulator_set_voltage_sel(struct regulator_dev *rdev,
					     unsigned selector)
{
	struct mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	struct mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	int id = rdev_get_id(rdev);

	return mc13xxx_reg_rmw(priv->mc13xxx, mc13xxx_regulators[id].vsel_reg,
			       mc13xxx_regulators[id].vsel_mask,
			       selector << mc13xxx_regulators[id].vsel_shift);
}