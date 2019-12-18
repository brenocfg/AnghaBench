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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct etnaviv_gpu {scalar_t__ sec_mode; } ;

/* Variables and functions */
 scalar_t__ ETNA_SEC_KERNEL ; 
 int /*<<< orphan*/  VIVS_FE_COMMAND_ADDRESS ; 
 int /*<<< orphan*/  VIVS_FE_COMMAND_CONTROL ; 
 int VIVS_FE_COMMAND_CONTROL_ENABLE ; 
 int VIVS_FE_COMMAND_CONTROL_PREFETCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIVS_MMUv2_SEC_COMMAND_CONTROL ; 
 int VIVS_MMUv2_SEC_COMMAND_CONTROL_ENABLE ; 
 int VIVS_MMUv2_SEC_COMMAND_CONTROL_PREFETCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 

void etnaviv_gpu_start_fe(struct etnaviv_gpu *gpu, u32 address, u16 prefetch)
{
	gpu_write(gpu, VIVS_FE_COMMAND_ADDRESS, address);
	gpu_write(gpu, VIVS_FE_COMMAND_CONTROL,
		  VIVS_FE_COMMAND_CONTROL_ENABLE |
		  VIVS_FE_COMMAND_CONTROL_PREFETCH(prefetch));

	if (gpu->sec_mode == ETNA_SEC_KERNEL) {
		gpu_write(gpu, VIVS_MMUv2_SEC_COMMAND_CONTROL,
			  VIVS_MMUv2_SEC_COMMAND_CONTROL_ENABLE |
			  VIVS_MMUv2_SEC_COMMAND_CONTROL_PREFETCH(prefetch));
	}
}