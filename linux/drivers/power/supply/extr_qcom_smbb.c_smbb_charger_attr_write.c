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
struct smbb_charger_attr {unsigned int max; unsigned int min; unsigned int (* hw_fn ) (unsigned int) ;int /*<<< orphan*/  name; scalar_t__ reg; scalar_t__ safe_reg; } ;
struct smbb_charger {unsigned int* attr; int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  regmap; } ;
typedef  enum smbb_attr { ____Placeholder_smbb_attr } smbb_attr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct smbb_charger_attr* smbb_charger_attrs ; 
 unsigned int smbb_hw_lookup (unsigned int,unsigned int (*) (unsigned int)) ; 
 unsigned int stub1 (unsigned int) ; 
 unsigned int stub2 (unsigned int) ; 

__attribute__((used)) static int smbb_charger_attr_write(struct smbb_charger *chg,
		enum smbb_attr which, unsigned int val)
{
	const struct smbb_charger_attr *prop;
	unsigned int wval;
	unsigned int out;
	int rc;

	prop = &smbb_charger_attrs[which];

	if (val > prop->max || val < prop->min) {
		dev_err(chg->dev, "value out of range for %s [%u:%u]\n",
			prop->name, prop->min, prop->max);
		return -EINVAL;
	}

	if (prop->safe_reg) {
		rc = regmap_read(chg->regmap,
				chg->addr + prop->safe_reg, &wval);
		if (rc) {
			dev_err(chg->dev,
				"unable to read safe value for '%s'\n",
				prop->name);
			return rc;
		}

		wval = prop->hw_fn(wval);

		if (val > wval) {
			dev_warn(chg->dev,
				"%s above safe value, clamping at %u\n",
				prop->name, wval);
			val = wval;
		}
	}

	wval = smbb_hw_lookup(val, prop->hw_fn);

	rc = regmap_write(chg->regmap, chg->addr + prop->reg, wval);
	if (rc) {
		dev_err(chg->dev, "unable to update %s", prop->name);
		return rc;
	}
	out = prop->hw_fn(wval);
	if (out != val) {
		dev_warn(chg->dev,
			"%s inaccurate, rounded to %u\n",
			prop->name, out);
	}

	dev_dbg(chg->dev, "%s <= %d\n", prop->name, out);

	chg->attr[which] = out;

	return 0;
}