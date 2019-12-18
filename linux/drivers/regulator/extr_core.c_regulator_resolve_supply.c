#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ parent; } ;
struct regulator_dev {int /*<<< orphan*/ * supply; scalar_t__ use_count; TYPE_2__ dev; TYPE_1__* desc; int /*<<< orphan*/  supply_name; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  _regulator_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_bound (scalar_t__) ; 
 struct regulator_dev* dummy_regulator_rdev ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 scalar_t__ have_full_constraints () ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 struct regulator_dev* regulator_dev_lookup (struct device*,int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int set_supply (struct regulator_dev*,struct regulator_dev*) ; 

__attribute__((used)) static int regulator_resolve_supply(struct regulator_dev *rdev)
{
	struct regulator_dev *r;
	struct device *dev = rdev->dev.parent;
	int ret;

	/* No supply to resolve? */
	if (!rdev->supply_name)
		return 0;

	/* Supply already resolved? */
	if (rdev->supply)
		return 0;

	r = regulator_dev_lookup(dev, rdev->supply_name);
	if (IS_ERR(r)) {
		ret = PTR_ERR(r);

		/* Did the lookup explicitly defer for us? */
		if (ret == -EPROBE_DEFER)
			return ret;

		if (have_full_constraints()) {
			r = dummy_regulator_rdev;
			get_device(&r->dev);
		} else {
			dev_err(dev, "Failed to resolve %s-supply for %s\n",
				rdev->supply_name, rdev->desc->name);
			return -EPROBE_DEFER;
		}
	}

	/*
	 * If the supply's parent device is not the same as the
	 * regulator's parent device, then ensure the parent device
	 * is bound before we resolve the supply, in case the parent
	 * device get probe deferred and unregisters the supply.
	 */
	if (r->dev.parent && r->dev.parent != rdev->dev.parent) {
		if (!device_is_bound(r->dev.parent)) {
			put_device(&r->dev);
			return -EPROBE_DEFER;
		}
	}

	/* Recursively resolve the supply of the supply */
	ret = regulator_resolve_supply(r);
	if (ret < 0) {
		put_device(&r->dev);
		return ret;
	}

	ret = set_supply(rdev, r);
	if (ret < 0) {
		put_device(&r->dev);
		return ret;
	}

	/*
	 * In set_machine_constraints() we may have turned this regulator on
	 * but we couldn't propagate to the supply if it hadn't been resolved
	 * yet.  Do it now.
	 */
	if (rdev->use_count) {
		ret = regulator_enable(rdev->supply);
		if (ret < 0) {
			_regulator_put(rdev->supply);
			rdev->supply = NULL;
			return ret;
		}
	}

	return 0;
}