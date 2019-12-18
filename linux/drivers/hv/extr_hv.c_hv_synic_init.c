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

/* Variables and functions */
 int /*<<< orphan*/  hv_stimer_init (unsigned int) ; 
 int /*<<< orphan*/  hv_synic_enable_regs (unsigned int) ; 

int hv_synic_init(unsigned int cpu)
{
	hv_synic_enable_regs(cpu);

	hv_stimer_init(cpu);

	return 0;
}