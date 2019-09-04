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
struct slice_data {int* level_to_irq; } ;
struct hub_data {int /*<<< orphan*/  slice_map; struct slice_data* slice; } ;
typedef  int /*<<< orphan*/  cnodeid_t ;
struct TYPE_2__ {struct slice_data* data; } ;

/* Variables and functions */
 int LEVELS_PER_SLICE ; 
 int LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_CPU_NUM ; 
 int SRB_DEV0 ; 
 int SRB_DEV1 ; 
 int /*<<< orphan*/  ST0_IM ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpu_data ; 
 int /*<<< orphan*/  cpu_time_init () ; 
 int /*<<< orphan*/  cputoslice (int) ; 
 int /*<<< orphan*/  get_compact_nodeid () ; 
 struct hub_data* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_cpu_nmi_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_ipi () ; 
 int /*<<< orphan*/  per_hub_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_c0_status (int) ; 
 int smp_processor_id () ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

void per_cpu_init(void)
{
	int cpu = smp_processor_id();
	int slice = LOCAL_HUB_L(PI_CPU_NUM);
	cnodeid_t cnode = get_compact_nodeid();
	struct hub_data *hub = hub_data(cnode);
	struct slice_data *si = hub->slice + slice;
	int i;

	if (test_and_set_bit(slice, &hub->slice_map))
		return;

	clear_c0_status(ST0_IM);

	per_hub_init(cnode);

	for (i = 0; i < LEVELS_PER_SLICE; i++)
		si->level_to_irq[i] = -1;

	/*
	 * We use this so we can find the local hub's data as fast as only
	 * possible.
	 */
	cpu_data[cpu].data = si;

	cpu_time_init();
	install_ipi();

	/* Install our NMI handler if symmon hasn't installed one. */
	install_cpu_nmi_handler(cputoslice(cpu));

	set_c0_status(SRB_DEV0 | SRB_DEV1);
}