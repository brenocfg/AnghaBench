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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  vma_node; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct drm_gem_vram_object {TYPE_2__ bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 

u64 drm_gem_vram_mmap_offset(struct drm_gem_vram_object *gbo)
{
	return drm_vma_node_offset_addr(&gbo->bo.base.vma_node);
}