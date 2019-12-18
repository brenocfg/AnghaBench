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
typedef  int /*<<< orphan*/  suspend_state_t ;
struct coupling_desc {int n_coupled; int n_resolved; struct regulator_dev** coupled_rdevs; struct regulator_coupler* coupler; } ;
struct regulator_dev {struct coupling_desc coupling_desc; } ;
struct regulator_coupler {int (* balance_voltage ) (struct regulator_coupler*,struct regulator_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PM_SUSPEND_ON ; 
 unsigned int abs (int) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 
 int regulator_get_optimal_voltage (struct regulator_dev*,int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int regulator_set_voltage_rdev (struct regulator_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int stub1 (struct regulator_coupler*,struct regulator_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static int regulator_balance_voltage(struct regulator_dev *rdev,
				     suspend_state_t state)
{
	struct regulator_dev **c_rdevs;
	struct regulator_dev *best_rdev;
	struct coupling_desc *c_desc = &rdev->coupling_desc;
	struct regulator_coupler *coupler = c_desc->coupler;
	int i, ret, n_coupled, best_min_uV, best_max_uV, best_c_rdev;
	unsigned int delta, best_delta;
	unsigned long c_rdev_done = 0;
	bool best_c_rdev_done;

	c_rdevs = c_desc->coupled_rdevs;
	n_coupled = c_desc->n_coupled;

	/*
	 * If system is in a state other than PM_SUSPEND_ON, don't check
	 * other coupled regulators.
	 */
	if (state != PM_SUSPEND_ON)
		n_coupled = 1;

	if (c_desc->n_resolved < n_coupled) {
		rdev_err(rdev, "Not all coupled regulators registered\n");
		return -EPERM;
	}

	/* Invoke custom balancer for customized couplers */
	if (coupler && coupler->balance_voltage)
		return coupler->balance_voltage(coupler, rdev, state);

	/*
	 * Find the best possible voltage change on each loop. Leave the loop
	 * if there isn't any possible change.
	 */
	do {
		best_c_rdev_done = false;
		best_delta = 0;
		best_min_uV = 0;
		best_max_uV = 0;
		best_c_rdev = 0;
		best_rdev = NULL;

		/*
		 * Find highest difference between optimal voltage
		 * and current voltage.
		 */
		for (i = 0; i < n_coupled; i++) {
			/*
			 * optimal_uV is the best voltage that can be set for
			 * i-th regulator at the moment without violating
			 * max_spread constraint in order to balance
			 * the coupled voltages.
			 */
			int optimal_uV = 0, optimal_max_uV = 0, current_uV = 0;

			if (test_bit(i, &c_rdev_done))
				continue;

			ret = regulator_get_optimal_voltage(c_rdevs[i],
							    &current_uV,
							    &optimal_uV,
							    &optimal_max_uV,
							    state, n_coupled);
			if (ret < 0)
				goto out;

			delta = abs(optimal_uV - current_uV);

			if (delta && best_delta <= delta) {
				best_c_rdev_done = ret;
				best_delta = delta;
				best_rdev = c_rdevs[i];
				best_min_uV = optimal_uV;
				best_max_uV = optimal_max_uV;
				best_c_rdev = i;
			}
		}

		/* Nothing to change, return successfully */
		if (!best_rdev) {
			ret = 0;
			goto out;
		}

		ret = regulator_set_voltage_rdev(best_rdev, best_min_uV,
						 best_max_uV, state);

		if (ret < 0)
			goto out;

		if (best_c_rdev_done)
			set_bit(best_c_rdev, &c_rdev_done);

	} while (n_coupled > 1);

out:
	return ret;
}