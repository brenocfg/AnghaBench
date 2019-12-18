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
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct etnaviv_vram_mapping {TYPE_2__ vram_node; struct etnaviv_gem_object* object; } ;
struct etnaviv_iommu_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct etnaviv_gem_object {TYPE_1__ base; int /*<<< orphan*/  sgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_2__*) ; 
 int /*<<< orphan*/  etnaviv_iommu_unmap (struct etnaviv_iommu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_iommu_remove_mapping(struct etnaviv_iommu_context *context,
	struct etnaviv_vram_mapping *mapping)
{
	struct etnaviv_gem_object *etnaviv_obj = mapping->object;

	etnaviv_iommu_unmap(context, mapping->vram_node.start,
			    etnaviv_obj->sgt, etnaviv_obj->base.size);
	drm_mm_remove_node(&mapping->vram_node);
}