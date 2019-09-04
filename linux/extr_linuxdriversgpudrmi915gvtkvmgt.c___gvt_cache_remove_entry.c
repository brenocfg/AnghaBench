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
struct TYPE_2__ {int /*<<< orphan*/  nr_cache_entries; int /*<<< orphan*/  dma_addr_cache; int /*<<< orphan*/  gfn_cache; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
struct gvt_dma {int /*<<< orphan*/  dma_addr_node; int /*<<< orphan*/  gfn_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gvt_dma*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __gvt_cache_remove_entry(struct intel_vgpu *vgpu,
				struct gvt_dma *entry)
{
	rb_erase(&entry->gfn_node, &vgpu->vdev.gfn_cache);
	rb_erase(&entry->dma_addr_node, &vgpu->vdev.dma_addr_cache);
	kfree(entry);
	vgpu->vdev.nr_cache_entries--;
}