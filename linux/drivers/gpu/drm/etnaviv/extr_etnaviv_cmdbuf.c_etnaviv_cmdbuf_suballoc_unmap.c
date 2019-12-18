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
struct etnaviv_vram_mapping {int dummy; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  etnaviv_iommu_put_suballoc_va (struct etnaviv_iommu_context*,struct etnaviv_vram_mapping*) ; 

void etnaviv_cmdbuf_suballoc_unmap(struct etnaviv_iommu_context *context,
				   struct etnaviv_vram_mapping *mapping)
{
	etnaviv_iommu_put_suballoc_va(context, mapping);
}