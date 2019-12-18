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
struct mc13xxx_regulator_priv {unsigned int powermisc_pwgt_state; int /*<<< orphan*/  mc13xxx; struct mc13xxx_regulator* mc13xxx_regulators; } ;
struct mc13xxx_regulator {unsigned int enable_bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int MC13783_REG_POWERMISC_PWGTSPI_M ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int mc13xxx_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 
 struct mc13xxx_regulator_priv* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int mc13783_gpo_regulator_is_enabled(struct regulator_dev *rdev)
{
	struct mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	struct mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	int ret, id = rdev_get_id(rdev);
	unsigned int val;

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_read(priv->mc13xxx, mc13xxx_regulators[id].reg, &val);
	mc13xxx_unlock(priv->mc13xxx);

	if (ret)
		return ret;

	/* Power Gates state is stored in powermisc_pwgt_state
	 * where the meaning of bits is negated */
	val = (val & ~MC13783_REG_POWERMISC_PWGTSPI_M) |
	      (priv->powermisc_pwgt_state ^ MC13783_REG_POWERMISC_PWGTSPI_M);

	return (val & mc13xxx_regulators[id].enable_bit) != 0;
}