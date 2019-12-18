#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct etnaviv_iommuv2_context {size_t id; int mtlb_dma; } ;
struct etnaviv_iommu_context {TYPE_2__* global; } ;
struct etnaviv_gpu {int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int* pta_cpu; int /*<<< orphan*/  pta_dma; } ;
struct TYPE_4__ {TYPE_1__ v2; int /*<<< orphan*/  bad_page_dma; } ;

/* Variables and functions */
 int VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K ; 
 int /*<<< orphan*/  VIVS_MMUv2_NONSEC_SAFE_ADDR_LOW ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_ADDRESS_HIGH ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_ADDRESS_LOW ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_CONTROL ; 
 int VIVS_MMUv2_PTA_CONTROL_ENABLE ; 
 int /*<<< orphan*/  VIVS_MMUv2_SAFE_ADDRESS_CONFIG ; 
 int VIVS_MMUv2_SAFE_ADDRESS_CONFIG_NON_SEC_SAFE_ADDR_HIGH (int) ; 
 int VIVS_MMUv2_SAFE_ADDRESS_CONFIG_SEC_SAFE_ADDR_HIGH (int) ; 
 int /*<<< orphan*/  VIVS_MMUv2_SEC_CONTROL ; 
 int VIVS_MMUv2_SEC_CONTROL_ENABLE ; 
 int /*<<< orphan*/  VIVS_MMUv2_SEC_SAFE_ADDR_LOW ; 
 int /*<<< orphan*/  etnaviv_buffer_config_pta (struct etnaviv_gpu*,size_t) ; 
 scalar_t__ etnaviv_cmdbuf_get_pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_gpu_start_fe (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_gpu_wait_idle (struct etnaviv_gpu*,int) ; 
 int gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_iommuv2_restore_sec(struct etnaviv_gpu *gpu,
	struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 prefetch;

	/* If the MMU is already enabled the state is still there. */
	if (gpu_read(gpu, VIVS_MMUv2_SEC_CONTROL) & VIVS_MMUv2_SEC_CONTROL_ENABLE)
		return;

	gpu_write(gpu, VIVS_MMUv2_PTA_ADDRESS_LOW,
		  lower_32_bits(context->global->v2.pta_dma));
	gpu_write(gpu, VIVS_MMUv2_PTA_ADDRESS_HIGH,
		  upper_32_bits(context->global->v2.pta_dma));
	gpu_write(gpu, VIVS_MMUv2_PTA_CONTROL, VIVS_MMUv2_PTA_CONTROL_ENABLE);

	gpu_write(gpu, VIVS_MMUv2_NONSEC_SAFE_ADDR_LOW,
		  lower_32_bits(context->global->bad_page_dma));
	gpu_write(gpu, VIVS_MMUv2_SEC_SAFE_ADDR_LOW,
		  lower_32_bits(context->global->bad_page_dma));
	gpu_write(gpu, VIVS_MMUv2_SAFE_ADDRESS_CONFIG,
		  VIVS_MMUv2_SAFE_ADDRESS_CONFIG_NON_SEC_SAFE_ADDR_HIGH(
		  upper_32_bits(context->global->bad_page_dma)) |
		  VIVS_MMUv2_SAFE_ADDRESS_CONFIG_SEC_SAFE_ADDR_HIGH(
		  upper_32_bits(context->global->bad_page_dma)));

	context->global->v2.pta_cpu[v2_context->id] = v2_context->mtlb_dma |
				 	 VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K;

	/* trigger a PTA load through the FE */
	prefetch = etnaviv_buffer_config_pta(gpu, v2_context->id);
	etnaviv_gpu_start_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffer),
			     prefetch);
	etnaviv_gpu_wait_idle(gpu, 100);

	gpu_write(gpu, VIVS_MMUv2_SEC_CONTROL, VIVS_MMUv2_SEC_CONTROL_ENABLE);
}