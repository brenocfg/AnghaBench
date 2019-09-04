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
typedef  int u64 ;
struct spu {TYPE_1__* priv1; int /*<<< orphan*/  node; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_route_RW; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  cpumask_intersects (struct cpumask const*,struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int /*<<< orphan*/ ) ; 
 int iic_get_target_id (int) ; 
 scalar_t__ nr_cpus_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cpu_affinity_set(struct spu *spu, int cpu)
{
	u64 target;
	u64 route;

	if (nr_cpus_node(spu->node)) {
		const struct cpumask *spumask = cpumask_of_node(spu->node),
			*cpumask = cpumask_of_node(cpu_to_node(cpu));

		if (!cpumask_intersects(spumask, cpumask))
			return;
	}

	target = iic_get_target_id(cpu);
	route = target << 48 | target << 32 | target << 16;
	out_be64(&spu->priv1->int_route_RW, route);
}