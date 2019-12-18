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
struct regulator_dev {struct regulation_constraints* constraints; } ;
struct regulation_constraints {int min_uV; int max_uV; int uV_offset; int min_uA; int max_uA; int valid_modes_mask; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  REGULATOR_CHANGE_VOLTAGE ; 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_IDLE ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 int _regulator_get_current_limit (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_dbg (struct regulator_dev*,char*,char*) ; 
 int /*<<< orphan*/  rdev_warn (struct regulator_dev*,char*) ; 
 int regulator_get_voltage_rdev (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void print_constraints(struct regulator_dev *rdev)
{
	struct regulation_constraints *constraints = rdev->constraints;
	char buf[160] = "";
	size_t len = sizeof(buf) - 1;
	int count = 0;
	int ret;

	if (constraints->min_uV && constraints->max_uV) {
		if (constraints->min_uV == constraints->max_uV)
			count += scnprintf(buf + count, len - count, "%d mV ",
					   constraints->min_uV / 1000);
		else
			count += scnprintf(buf + count, len - count,
					   "%d <--> %d mV ",
					   constraints->min_uV / 1000,
					   constraints->max_uV / 1000);
	}

	if (!constraints->min_uV ||
	    constraints->min_uV != constraints->max_uV) {
		ret = regulator_get_voltage_rdev(rdev);
		if (ret > 0)
			count += scnprintf(buf + count, len - count,
					   "at %d mV ", ret / 1000);
	}

	if (constraints->uV_offset)
		count += scnprintf(buf + count, len - count, "%dmV offset ",
				   constraints->uV_offset / 1000);

	if (constraints->min_uA && constraints->max_uA) {
		if (constraints->min_uA == constraints->max_uA)
			count += scnprintf(buf + count, len - count, "%d mA ",
					   constraints->min_uA / 1000);
		else
			count += scnprintf(buf + count, len - count,
					   "%d <--> %d mA ",
					   constraints->min_uA / 1000,
					   constraints->max_uA / 1000);
	}

	if (!constraints->min_uA ||
	    constraints->min_uA != constraints->max_uA) {
		ret = _regulator_get_current_limit(rdev);
		if (ret > 0)
			count += scnprintf(buf + count, len - count,
					   "at %d mA ", ret / 1000);
	}

	if (constraints->valid_modes_mask & REGULATOR_MODE_FAST)
		count += scnprintf(buf + count, len - count, "fast ");
	if (constraints->valid_modes_mask & REGULATOR_MODE_NORMAL)
		count += scnprintf(buf + count, len - count, "normal ");
	if (constraints->valid_modes_mask & REGULATOR_MODE_IDLE)
		count += scnprintf(buf + count, len - count, "idle ");
	if (constraints->valid_modes_mask & REGULATOR_MODE_STANDBY)
		count += scnprintf(buf + count, len - count, "standby");

	if (!count)
		scnprintf(buf, len, "no parameters");

	rdev_dbg(rdev, "%s\n", buf);

	if ((constraints->min_uV != constraints->max_uV) &&
	    !regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE))
		rdev_warn(rdev,
			  "Voltage range but no REGULATOR_CHANGE_VOLTAGE\n");
}