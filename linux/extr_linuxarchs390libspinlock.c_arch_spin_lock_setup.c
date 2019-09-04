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
struct spin_wait {int node_id; } ;

/* Variables and functions */
 int _Q_TAIL_CPU_OFFSET ; 
 int _Q_TAIL_IDX_OFFSET ; 
 int /*<<< orphan*/  memset (struct spin_wait*,int /*<<< orphan*/ ,int) ; 
 struct spin_wait* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * spin_wait ; 

void arch_spin_lock_setup(int cpu)
{
	struct spin_wait *node;
	int ix;

	node = per_cpu_ptr(&spin_wait[0], cpu);
	for (ix = 0; ix < 4; ix++, node++) {
		memset(node, 0, sizeof(*node));
		node->node_id = ((cpu + 1) << _Q_TAIL_CPU_OFFSET) +
			(ix << _Q_TAIL_IDX_OFFSET);
	}
}