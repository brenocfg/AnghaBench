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
struct regulation_constraints {scalar_t__ max_uV_step; } ;

/* Variables and functions */
 int /*<<< orphan*/  _regulator_is_enabled (struct regulator_dev*) ; 
 scalar_t__ abs (int) ; 
 int max (scalar_t__,int) ; 
 int min (scalar_t__,int) ; 
 int regulator_get_voltage_rdev (struct regulator_dev*) ; 

__attribute__((used)) static int regulator_limit_voltage_step(struct regulator_dev *rdev,
					int *current_uV, int *min_uV)
{
	struct regulation_constraints *constraints = rdev->constraints;

	/* Limit voltage change only if necessary */
	if (!constraints->max_uV_step || !_regulator_is_enabled(rdev))
		return 1;

	if (*current_uV < 0) {
		*current_uV = regulator_get_voltage_rdev(rdev);

		if (*current_uV < 0)
			return *current_uV;
	}

	if (abs(*current_uV - *min_uV) <= constraints->max_uV_step)
		return 1;

	/* Clamp target voltage within the given step */
	if (*current_uV < *min_uV)
		*min_uV = min(*current_uV + constraints->max_uV_step,
			      *min_uV);
	else
		*min_uV = max(*current_uV - constraints->max_uV_step,
			      *min_uV);

	return 0;
}