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
 int /*<<< orphan*/  BUG () ; 
 int GRU_NUM_TFM ; 
 int UVH_GR0_TLB_INT0_CONFIG ; 
 int UVH_GR0_TLB_INT1_CONFIG ; 
 int UVH_GR1_TLB_INT0_CONFIG ; 
 int UVH_GR1_TLB_INT1_CONFIG ; 
 int UV_MAX_INT_CORES ; 
 int uv_cpu_core_number (int) ; 
 scalar_t__ uv_cpu_ht_number (int) ; 
 int uv_cpu_socket_number (int) ; 

__attribute__((used)) static unsigned long gru_chiplet_cpu_to_mmr(int chiplet, int cpu, int *corep)
{
	unsigned long mmr = 0;
	int core;

	/*
	 * We target the cores of a blade and not the hyperthreads themselves.
	 * There is a max of 8 cores per socket and 2 sockets per blade,
	 * making for a max total of 16 cores (i.e., 16 CPUs without
	 * hyperthreading and 32 CPUs with hyperthreading).
	 */
	core = uv_cpu_core_number(cpu) + UV_MAX_INT_CORES * uv_cpu_socket_number(cpu);
	if (core >= GRU_NUM_TFM || uv_cpu_ht_number(cpu))
		return 0;

	if (chiplet == 0) {
		mmr = UVH_GR0_TLB_INT0_CONFIG +
		    core * (UVH_GR0_TLB_INT1_CONFIG - UVH_GR0_TLB_INT0_CONFIG);
	} else if (chiplet == 1) {
		mmr = UVH_GR1_TLB_INT0_CONFIG +
		    core * (UVH_GR1_TLB_INT1_CONFIG - UVH_GR1_TLB_INT0_CONFIG);
	} else {
		BUG();
	}

	*corep = core;
	return mmr;
}