#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct reg_action {int value; int /*<<< orphan*/  reg; int /*<<< orphan*/  mask; } ;
struct rapl_primitive_info {int flag; size_t id; int shift; int /*<<< orphan*/  unit; int /*<<< orphan*/  mask; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int* primitives; } ;
struct rapl_domain {size_t id; TYPE_3__* rp; TYPE_1__ rdd; int /*<<< orphan*/ * regs; } ;
typedef  enum rapl_primitives { ____Placeholder_rapl_primitives } rapl_primitives ;
struct TYPE_6__ {int lead_cpu; TYPE_2__* priv; } ;
struct TYPE_5__ {int* limits; scalar_t__ (* read_raw ) (int,struct reg_action*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int FW_LOCK ; 
 int /*<<< orphan*/  POWER_HIGH_LOCK ; 
 int RAPL_PRIMITIVE_DERIVED ; 
 int RAPL_PRIMITIVE_DUMMY ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int rapl_unit_xlate (struct rapl_domain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rapl_primitive_info* rpi ; 
 scalar_t__ stub1 (int,struct reg_action*) ; 

__attribute__((used)) static int rapl_read_data_raw(struct rapl_domain *rd,
			      enum rapl_primitives prim, bool xlate, u64 *data)
{
	u64 value;
	struct rapl_primitive_info *rp = &rpi[prim];
	struct reg_action ra;
	int cpu;

	if (!rp->name || rp->flag & RAPL_PRIMITIVE_DUMMY)
		return -EINVAL;

	ra.reg = rd->regs[rp->id];
	if (!ra.reg)
		return -EINVAL;

	cpu = rd->rp->lead_cpu;

	/* domain with 2 limits has different bit */
	if (prim == FW_LOCK && rd->rp->priv->limits[rd->id] == 2) {
		rp->mask = POWER_HIGH_LOCK;
		rp->shift = 63;
	}
	/* non-hardware data are collected by the polling thread */
	if (rp->flag & RAPL_PRIMITIVE_DERIVED) {
		*data = rd->rdd.primitives[prim];
		return 0;
	}

	ra.mask = rp->mask;

	if (rd->rp->priv->read_raw(cpu, &ra)) {
		pr_debug("failed to read reg 0x%llx on cpu %d\n", ra.reg, cpu);
		return -EIO;
	}

	value = ra.value >> rp->shift;

	if (xlate)
		*data = rapl_unit_xlate(rd, rp->unit, value, 0);
	else
		*data = value;

	return 0;
}