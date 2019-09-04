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
typedef  int /*<<< orphan*/  u64 ;
struct imc_mem_info {scalar_t__ vbase; } ;
struct TYPE_2__ {int counter_mem_size; struct imc_mem_info* mem_info; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* core_imc_pmu ; 
 struct imc_mem_info* core_imc_refc ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct imc_mem_info*) ; 
 int /*<<< orphan*/  num_possible_cpus () ; 
 int /*<<< orphan*/  threads_per_core ; 

__attribute__((used)) static void cleanup_all_core_imc_memory(void)
{
	int i, nr_cores = DIV_ROUND_UP(num_possible_cpus(), threads_per_core);
	struct imc_mem_info *ptr = core_imc_pmu->mem_info;
	int size = core_imc_pmu->counter_mem_size;

	/* mem_info will never be NULL */
	for (i = 0; i < nr_cores; i++) {
		if (ptr[i].vbase)
			free_pages((u64)ptr[i].vbase, get_order(size));
	}

	kfree(ptr);
	kfree(core_imc_refc);
}