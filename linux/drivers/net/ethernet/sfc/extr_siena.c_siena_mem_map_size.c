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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 unsigned int FR_CZ_MC_TREG_SMEM ; 
 int FR_CZ_MC_TREG_SMEM_ROWS ; 
 int FR_CZ_MC_TREG_SMEM_STEP ; 

__attribute__((used)) static unsigned int siena_mem_map_size(struct efx_nic *efx)
{
	return FR_CZ_MC_TREG_SMEM +
		FR_CZ_MC_TREG_SMEM_STEP * FR_CZ_MC_TREG_SMEM_ROWS;
}