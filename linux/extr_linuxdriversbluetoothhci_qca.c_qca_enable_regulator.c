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
struct regulator {int dummy; } ;
struct qca_vreg {scalar_t__ load_uA; int /*<<< orphan*/  max_uV; int /*<<< orphan*/  min_uV; } ;

/* Variables and functions */
 int regulator_enable (struct regulator*) ; 
 int regulator_set_load (struct regulator*,scalar_t__) ; 
 int regulator_set_voltage (struct regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_enable_regulator(struct qca_vreg vregs,
				struct regulator *regulator)
{
	int ret;

	ret = regulator_set_voltage(regulator, vregs.min_uV,
				    vregs.max_uV);
	if (ret)
		return ret;

	if (vregs.load_uA)
		ret = regulator_set_load(regulator,
					 vregs.load_uA);

	if (ret)
		return ret;

	return regulator_enable(regulator);

}