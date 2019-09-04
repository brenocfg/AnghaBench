#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_object {TYPE_2__* vram_node; } ;
struct TYPE_6__ {int paddr; } ;
struct msm_drm_private {TYPE_3__ vram; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {scalar_t__ start; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static dma_addr_t physaddr(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct msm_drm_private *priv = obj->dev->dev_private;
	return (((dma_addr_t)msm_obj->vram_node->start) << PAGE_SHIFT) +
			priv->vram.paddr;
}