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
struct rockchip_gem_object {scalar_t__ pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  rockchip_gem_free_dma (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_free_iommu (struct rockchip_gem_object*) ; 

__attribute__((used)) static void rockchip_gem_free_buf(struct rockchip_gem_object *rk_obj)
{
	if (rk_obj->pages)
		rockchip_gem_free_iommu(rk_obj);
	else
		rockchip_gem_free_dma(rk_obj);
}