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
typedef  scalar_t__ u64 ;
struct etnaviv_iommu_context {int /*<<< orphan*/  mm; } ;
struct drm_mm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_INSERT_LOWEST ; 
 int drm_mm_insert_node_in_range (int /*<<< orphan*/ *,struct drm_mm_node*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etnaviv_iommu_insert_exact(struct etnaviv_iommu_context *context,
		   struct drm_mm_node *node, size_t size, u64 va)
{
	return drm_mm_insert_node_in_range(&context->mm, node, size, 0, 0, va,
					   va + size, DRM_MM_INSERT_LOWEST);
}