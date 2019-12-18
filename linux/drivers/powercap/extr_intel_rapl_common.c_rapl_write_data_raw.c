#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct reg_action {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct rapl_primitive_info {size_t id; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  unit; } ;
struct rapl_domain {TYPE_2__* rp; int /*<<< orphan*/ * regs; } ;
typedef  int /*<<< orphan*/  ra ;
typedef  enum rapl_primitives { ____Placeholder_rapl_primitives } rapl_primitives ;
struct TYPE_4__ {int lead_cpu; TYPE_1__* priv; } ;
struct TYPE_3__ {int (* write_raw ) (int,struct reg_action*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct reg_action*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rapl_unit_xlate (struct rapl_domain*,int /*<<< orphan*/ ,unsigned long long,int) ; 
 struct rapl_primitive_info* rpi ; 
 int stub1 (int,struct reg_action*) ; 

__attribute__((used)) static int rapl_write_data_raw(struct rapl_domain *rd,
			       enum rapl_primitives prim,
			       unsigned long long value)
{
	struct rapl_primitive_info *rp = &rpi[prim];
	int cpu;
	u64 bits;
	struct reg_action ra;
	int ret;

	cpu = rd->rp->lead_cpu;
	bits = rapl_unit_xlate(rd, rp->unit, value, 1);
	bits <<= rp->shift;
	bits &= rp->mask;

	memset(&ra, 0, sizeof(ra));

	ra.reg = rd->regs[rp->id];
	ra.mask = rp->mask;
	ra.value = bits;

	ret = rd->rp->priv->write_raw(cpu, &ra);

	return ret;
}