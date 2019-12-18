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
typedef  scalar_t__ u32 ;
struct etnaviv_iommuv1_context {scalar_t__ pgtable_dma; } ;
struct etnaviv_iommu_context {TYPE_1__* global; } ;
struct etnaviv_gpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ memory_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_MC_MEMORY_BASE_ADDR_FE ; 
 int /*<<< orphan*/  VIVS_MC_MEMORY_BASE_ADDR_PE ; 
 int /*<<< orphan*/  VIVS_MC_MEMORY_BASE_ADDR_PEZ ; 
 int /*<<< orphan*/  VIVS_MC_MEMORY_BASE_ADDR_RA ; 
 int /*<<< orphan*/  VIVS_MC_MEMORY_BASE_ADDR_TX ; 
 int /*<<< orphan*/  VIVS_MC_MMU_FE_PAGE_TABLE ; 
 int /*<<< orphan*/  VIVS_MC_MMU_PEZ_PAGE_TABLE ; 
 int /*<<< orphan*/  VIVS_MC_MMU_PE_PAGE_TABLE ; 
 int /*<<< orphan*/  VIVS_MC_MMU_RA_PAGE_TABLE ; 
 int /*<<< orphan*/  VIVS_MC_MMU_TX_PAGE_TABLE ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct etnaviv_iommuv1_context* to_v1_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv1_restore(struct etnaviv_gpu *gpu,
			     struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv1_context *v1_context = to_v1_context(context);
	u32 pgtable;

	/* set base addresses */
	gpu_write(gpu, VIVS_MC_MEMORY_BASE_ADDR_RA, context->global->memory_base);
	gpu_write(gpu, VIVS_MC_MEMORY_BASE_ADDR_FE, context->global->memory_base);
	gpu_write(gpu, VIVS_MC_MEMORY_BASE_ADDR_TX, context->global->memory_base);
	gpu_write(gpu, VIVS_MC_MEMORY_BASE_ADDR_PEZ, context->global->memory_base);
	gpu_write(gpu, VIVS_MC_MEMORY_BASE_ADDR_PE, context->global->memory_base);

	/* set page table address in MC */
	pgtable = (u32)v1_context->pgtable_dma;

	gpu_write(gpu, VIVS_MC_MMU_FE_PAGE_TABLE, pgtable);
	gpu_write(gpu, VIVS_MC_MMU_TX_PAGE_TABLE, pgtable);
	gpu_write(gpu, VIVS_MC_MMU_PE_PAGE_TABLE, pgtable);
	gpu_write(gpu, VIVS_MC_MMU_PEZ_PAGE_TABLE, pgtable);
	gpu_write(gpu, VIVS_MC_MMU_RA_PAGE_TABLE, pgtable);
}