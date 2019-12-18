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
struct TYPE_2__ {int /*<<< orphan*/  cache_lock; scalar_t__ nr_cache_entries; void* dma_addr_cache; void* gfn_cache; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 void* RB_ROOT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gvt_cache_init(struct intel_vgpu *vgpu)
{
	vgpu->vdev.gfn_cache = RB_ROOT;
	vgpu->vdev.dma_addr_cache = RB_ROOT;
	vgpu->vdev.nr_cache_entries = 0;
	mutex_init(&vgpu->vdev.cache_lock);
}