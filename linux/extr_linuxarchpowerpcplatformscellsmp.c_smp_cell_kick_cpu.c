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
struct TYPE_2__ {int cpu_start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int nr_cpu_ids ; 
 TYPE_1__** paca_ptrs ; 
 int /*<<< orphan*/  smp_startup_cpu (int) ; 

__attribute__((used)) static int smp_cell_kick_cpu(int nr)
{
	if (nr < 0 || nr >= nr_cpu_ids)
		return -EINVAL;

	if (!smp_startup_cpu(nr))
		return -ENOENT;

	/*
	 * The processor is currently spinning, waiting for the
	 * cpu_start field to become non-zero After we set cpu_start,
	 * the processor will continue on to secondary_start
	 */
	paca_ptrs[nr]->cpu_start = 1;

	return 0;
}