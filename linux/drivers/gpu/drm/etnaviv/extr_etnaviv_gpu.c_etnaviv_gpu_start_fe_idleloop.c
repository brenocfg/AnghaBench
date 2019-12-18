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
struct etnaviv_gpu {TYPE_1__* mmu_context; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdbuf_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  etnaviv_buffer_init (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_get_va (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_gpu_start_fe (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_iommu_restore (struct etnaviv_gpu*,TYPE_1__*) ; 

__attribute__((used)) static void etnaviv_gpu_start_fe_idleloop(struct etnaviv_gpu *gpu)
{
	u32 address = etnaviv_cmdbuf_get_va(&gpu->buffer,
				&gpu->mmu_context->cmdbuf_mapping);
	u16 prefetch;

	/* setup the MMU */
	etnaviv_iommu_restore(gpu, gpu->mmu_context);

	/* Start command processor */
	prefetch = etnaviv_buffer_init(gpu);

	etnaviv_gpu_start_fe(gpu, address, prefetch);
}