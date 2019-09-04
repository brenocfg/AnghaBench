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
struct qca_vreg {scalar_t__ load_uA; int /*<<< orphan*/  max_uV; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 int /*<<< orphan*/  regulator_set_load (struct regulator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_voltage (struct regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qca_disable_regulator(struct qca_vreg vregs,
				  struct regulator *regulator)
{
	regulator_disable(regulator);
	regulator_set_voltage(regulator, 0, vregs.max_uV);
	if (vregs.load_uA)
		regulator_set_load(regulator, 0);

}