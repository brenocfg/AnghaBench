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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct etnaviv_iommuv2_context {scalar_t__ mtlb_dma; } ;
struct etnaviv_iommu_context {TYPE_1__* global; } ;
struct etnaviv_gpu {int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {scalar_t__ bad_page_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_MMUv2_CONTROL ; 
 int VIVS_MMUv2_CONTROL_ENABLE ; 
 int /*<<< orphan*/  etnaviv_buffer_config_mmuv2 (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ etnaviv_cmdbuf_get_pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_gpu_start_fe (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_gpu_wait_idle (struct etnaviv_gpu*,int) ; 
 int gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv2_restore_nonsec(struct etnaviv_gpu *gpu,
	struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 prefetch;

	/* If the MMU is already enabled the state is still there. */
	if (gpu_read(gpu, VIVS_MMUv2_CONTROL) & VIVS_MMUv2_CONTROL_ENABLE)
		return;

	prefetch = etnaviv_buffer_config_mmuv2(gpu,
				(u32)v2_context->mtlb_dma,
				(u32)context->global->bad_page_dma);
	etnaviv_gpu_start_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffer),
			     prefetch);
	etnaviv_gpu_wait_idle(gpu, 100);

	gpu_write(gpu, VIVS_MMUv2_CONTROL, VIVS_MMUv2_CONTROL_ENABLE);
}