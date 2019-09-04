#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct its_node {int flags; scalar_t__ numa_node; TYPE_1__* collections; scalar_t__ base; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int phys_base; } ;
struct TYPE_4__ {int target_address; int col_id; } ;

/* Variables and functions */
 scalar_t__ GICR_TYPER ; 
 int GICR_TYPER_CPU_NUMBER (int) ; 
 scalar_t__ GITS_TYPER ; 
 int GITS_TYPER_PTA ; 
 int ITS_FLAGS_WORKAROUND_CAVIUM_23144 ; 
 scalar_t__ NUMA_NO_NODE ; 
 TYPE_3__* gic_data_rdist () ; 
 scalar_t__ gic_data_rdist_rd_base () ; 
 int gic_read_typer (scalar_t__) ; 
 int /*<<< orphan*/  its_send_invall (struct its_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  its_send_mapc (struct its_node*,TYPE_1__*,int) ; 
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 
 scalar_t__ of_node_to_nid (struct device_node*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void its_cpu_init_collection(struct its_node *its)
{
	int cpu = smp_processor_id();
	u64 target;

	/* avoid cross node collections and its mapping */
	if (its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_23144) {
		struct device_node *cpu_node;

		cpu_node = of_get_cpu_node(cpu, NULL);
		if (its->numa_node != NUMA_NO_NODE &&
			its->numa_node != of_node_to_nid(cpu_node))
			return;
	}

	/*
	 * We now have to bind each collection to its target
	 * redistributor.
	 */
	if (gic_read_typer(its->base + GITS_TYPER) & GITS_TYPER_PTA) {
		/*
		 * This ITS wants the physical address of the
		 * redistributor.
		 */
		target = gic_data_rdist()->phys_base;
	} else {
		/* This ITS wants a linear CPU number. */
		target = gic_read_typer(gic_data_rdist_rd_base() + GICR_TYPER);
		target = GICR_TYPER_CPU_NUMBER(target) << 16;
	}

	/* Perform collection mapping */
	its->collections[cpu].target_address = target;
	its->collections[cpu].col_id = cpu;

	its_send_mapc(its, &its->collections[cpu], 1);
	its_send_invall(its, &its->collections[cpu]);
}