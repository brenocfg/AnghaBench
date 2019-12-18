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
typedef  int /*<<< orphan*/  u32 ;
struct etnaviv_vram_mapping {int dummy; } ;
struct etnaviv_iommu_context {int dummy; } ;
struct etnaviv_cmdbuf_suballoc {int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUBALLOC_SIZE ; 
 int etnaviv_iommu_get_suballoc_va (struct etnaviv_iommu_context*,struct etnaviv_vram_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int etnaviv_cmdbuf_suballoc_map(struct etnaviv_cmdbuf_suballoc *suballoc,
				struct etnaviv_iommu_context *context,
				struct etnaviv_vram_mapping *mapping,
				u32 memory_base)
{
	return etnaviv_iommu_get_suballoc_va(context, mapping, memory_base,
					     suballoc->paddr, SUBALLOC_SIZE);
}