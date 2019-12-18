#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct reg_action {int value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct rapl_package {int energy_unit; int power_unit; int time_unit; int /*<<< orphan*/  name; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_unit; scalar_t__ (* read_raw ) (int,struct reg_action*) ;} ;

/* Variables and functions */
 int ENERGY_UNIT_MASK ; 
 int ENERGY_UNIT_OFFSET ; 
 int ENERGY_UNIT_SCALE ; 
 int ENODEV ; 
 int POWER_UNIT_MASK ; 
 int POWER_UNIT_OFFSET ; 
 int TIME_UNIT_MASK ; 
 int TIME_UNIT_OFFSET ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int,struct reg_action*) ; 

__attribute__((used)) static int rapl_check_unit_atom(struct rapl_package *rp, int cpu)
{
	struct reg_action ra;
	u32 value;

	ra.reg = rp->priv->reg_unit;
	ra.mask = ~0;
	if (rp->priv->read_raw(cpu, &ra)) {
		pr_err("Failed to read power unit REG 0x%llx on CPU %d, exit.\n",
		       rp->priv->reg_unit, cpu);
		return -ENODEV;
	}

	value = (ra.value & ENERGY_UNIT_MASK) >> ENERGY_UNIT_OFFSET;
	rp->energy_unit = ENERGY_UNIT_SCALE * 1 << value;

	value = (ra.value & POWER_UNIT_MASK) >> POWER_UNIT_OFFSET;
	rp->power_unit = (1 << value) * 1000;

	value = (ra.value & TIME_UNIT_MASK) >> TIME_UNIT_OFFSET;
	rp->time_unit = 1000000 / (1 << value);

	pr_debug("Atom %s energy=%dpJ, time=%dus, power=%duW\n",
		 rp->name, rp->energy_unit, rp->time_unit, rp->power_unit);

	return 0;
}