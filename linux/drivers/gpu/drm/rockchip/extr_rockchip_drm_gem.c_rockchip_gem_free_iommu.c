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
struct rockchip_gem_object {int /*<<< orphan*/  kvaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rockchip_gem_iommu_unmap (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_put_pages (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_gem_free_iommu(struct rockchip_gem_object *rk_obj)
{
	vunmap(rk_obj->kvaddr);
	rockchip_gem_iommu_unmap(rk_obj);
	rockchip_gem_put_pages(rk_obj);
}