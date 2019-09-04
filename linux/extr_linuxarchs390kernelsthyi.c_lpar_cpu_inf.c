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
struct cpu_inf {int cpu_num_ded; int cpu_num_shd; int lpar_weight; int all_weight; int /*<<< orphan*/  lpar_grp_cap; int /*<<< orphan*/  lpar_cap; } ;
struct lpar_cpu_inf {struct cpu_inf ifl; struct cpu_inf cp; } ;
struct TYPE_3__ {int rcpus; } ;
struct diag204_x_part_block {TYPE_2__* cpus; TYPE_1__ hdr; } ;
struct TYPE_4__ {int cflag; scalar_t__ cur_weight; scalar_t__ weight; int /*<<< orphan*/  group_cpu_type_cap; int /*<<< orphan*/  cpu_type_cap; int /*<<< orphan*/  ctidx; } ;

/* Variables and functions */
#define  CP 129 
 scalar_t__ DED_WEIGHT ; 
 int DIAG204_CPU_CAPPED ; 
 int DIAG204_CPU_ONLINE ; 
#define  IFL 128 
 int cpu_id (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct diag204_x_part_block *lpar_cpu_inf(struct lpar_cpu_inf *part_inf,
						 bool this_lpar,
						 void *diag224_buf,
						 struct diag204_x_part_block *block)
{
	int i, capped = 0, weight_cp = 0, weight_ifl = 0;
	struct cpu_inf *cpu_inf;

	for (i = 0; i < block->hdr.rcpus; i++) {
		if (!(block->cpus[i].cflag & DIAG204_CPU_ONLINE))
			continue;

		switch (cpu_id(block->cpus[i].ctidx, diag224_buf)) {
		case CP:
			cpu_inf = &part_inf->cp;
			if (block->cpus[i].cur_weight < DED_WEIGHT)
				weight_cp |= block->cpus[i].cur_weight;
			break;
		case IFL:
			cpu_inf = &part_inf->ifl;
			if (block->cpus[i].cur_weight < DED_WEIGHT)
				weight_ifl |= block->cpus[i].cur_weight;
			break;
		default:
			continue;
		}

		if (!this_lpar)
			continue;

		capped |= block->cpus[i].cflag & DIAG204_CPU_CAPPED;
		cpu_inf->lpar_cap |= block->cpus[i].cpu_type_cap;
		cpu_inf->lpar_grp_cap |= block->cpus[i].group_cpu_type_cap;

		if (block->cpus[i].weight == DED_WEIGHT)
			cpu_inf->cpu_num_ded += 1;
		else
			cpu_inf->cpu_num_shd += 1;
	}

	if (this_lpar && capped) {
		part_inf->cp.lpar_weight = weight_cp;
		part_inf->ifl.lpar_weight = weight_ifl;
	}
	part_inf->cp.all_weight += weight_cp;
	part_inf->ifl.all_weight += weight_ifl;
	return (struct diag204_x_part_block *)&block->cpus[i];
}