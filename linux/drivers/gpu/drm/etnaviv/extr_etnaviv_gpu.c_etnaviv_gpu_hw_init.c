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
typedef  int u32 ;
struct TYPE_2__ {int revision; } ;
struct etnaviv_gpu {scalar_t__ sec_mode; TYPE_1__ identity; } ;

/* Variables and functions */
 scalar_t__ ETNA_SEC_KERNEL ; 
 int /*<<< orphan*/  GC2000 ; 
 int /*<<< orphan*/  GC320 ; 
 int /*<<< orphan*/  VIVS_HI_AXI_CONFIG ; 
 unsigned int VIVS_HI_AXI_CONFIG_ARCACHE (int) ; 
 unsigned int VIVS_HI_AXI_CONFIG_AWCACHE (int) ; 
 int /*<<< orphan*/  VIVS_HI_CHIP_TIME ; 
 int /*<<< orphan*/  VIVS_HI_INTR_ENBL ; 
 int /*<<< orphan*/  VIVS_MC_BUS_CONFIG ; 
 int VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG (int) ; 
 int VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__MASK ; 
 int VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG (int /*<<< orphan*/ ) ; 
 int VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__MASK ; 
 int /*<<< orphan*/  VIVS_MC_DEBUG_MEMORY ; 
 int /*<<< orphan*/  VIVS_MMUv2_AHB_CONTROL ; 
 int VIVS_MMUv2_AHB_CONTROL_NONSEC_ACCESS ; 
 int /*<<< orphan*/  etnaviv_gpu_enable_mlcg (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_gpu_setup_pulse_eater (struct etnaviv_gpu*) ; 
 scalar_t__ etnaviv_is_model_rev (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 
 int gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void etnaviv_gpu_hw_init(struct etnaviv_gpu *gpu)
{
	if ((etnaviv_is_model_rev(gpu, GC320, 0x5007) ||
	     etnaviv_is_model_rev(gpu, GC320, 0x5220)) &&
	    gpu_read(gpu, VIVS_HI_CHIP_TIME) != 0x2062400) {
		u32 mc_memory_debug;

		mc_memory_debug = gpu_read(gpu, VIVS_MC_DEBUG_MEMORY) & ~0xff;

		if (gpu->identity.revision == 0x5007)
			mc_memory_debug |= 0x0c;
		else
			mc_memory_debug |= 0x08;

		gpu_write(gpu, VIVS_MC_DEBUG_MEMORY, mc_memory_debug);
	}

	/* enable module-level clock gating */
	etnaviv_gpu_enable_mlcg(gpu);

	/*
	 * Update GPU AXI cache atttribute to "cacheable, no allocate".
	 * This is necessary to prevent the iMX6 SoC locking up.
	 */
	gpu_write(gpu, VIVS_HI_AXI_CONFIG,
		  VIVS_HI_AXI_CONFIG_AWCACHE(2) |
		  VIVS_HI_AXI_CONFIG_ARCACHE(2));

	/* GC2000 rev 5108 needs a special bus config */
	if (etnaviv_is_model_rev(gpu, GC2000, 0x5108)) {
		u32 bus_config = gpu_read(gpu, VIVS_MC_BUS_CONFIG);
		bus_config &= ~(VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__MASK |
				VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__MASK);
		bus_config |= VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG(1) |
			      VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG(0);
		gpu_write(gpu, VIVS_MC_BUS_CONFIG, bus_config);
	}

	if (gpu->sec_mode == ETNA_SEC_KERNEL) {
		u32 val = gpu_read(gpu, VIVS_MMUv2_AHB_CONTROL);
		val |= VIVS_MMUv2_AHB_CONTROL_NONSEC_ACCESS;
		gpu_write(gpu, VIVS_MMUv2_AHB_CONTROL, val);
	}

	/* setup the pulse eater */
	etnaviv_gpu_setup_pulse_eater(gpu);

	gpu_write(gpu, VIVS_HI_INTR_ENBL, ~0U);
}