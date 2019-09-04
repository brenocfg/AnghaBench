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
 int thread_imc_mem_alloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_imc_mem_size ; 

__attribute__((used)) static int ppc_thread_imc_cpu_online(unsigned int cpu)
{
	return thread_imc_mem_alloc(cpu, thread_imc_mem_size);
}