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
struct fam15h_power_data {int* cu_on; int /*<<< orphan*/ * cpu_sw_pwr_ptsc; int /*<<< orphan*/ * cu_acc_power; } ;
struct TYPE_2__ {int cpu_core_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F15H_CU_PWR_ACCUMULATOR ; 
 int /*<<< orphan*/  MSR_F15H_PTSC ; 
 TYPE_1__ cpu_data (int) ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void do_read_registers_on_cu(void *_data)
{
	struct fam15h_power_data *data = _data;
	int cpu, cu;

	cpu = smp_processor_id();

	/*
	 * With the new x86 topology modelling, cpu core id actually
	 * is compute unit id.
	 */
	cu = cpu_data(cpu).cpu_core_id;

	rdmsrl_safe(MSR_F15H_CU_PWR_ACCUMULATOR, &data->cu_acc_power[cu]);
	rdmsrl_safe(MSR_F15H_PTSC, &data->cpu_sw_pwr_ptsc[cu]);

	data->cu_on[cu] = 1;
}