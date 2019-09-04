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
struct kvmppc_vpa {int dirty; unsigned long gpa; int /*<<< orphan*/  pinned_addr; } ;
struct kvm_memory_slot {unsigned long base_gfn; unsigned long npages; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __set_bit_le (unsigned long,unsigned long*) ; 

void kvmppc_harvest_vpa_dirty(struct kvmppc_vpa *vpa,
			      struct kvm_memory_slot *memslot,
			      unsigned long *map)
{
	unsigned long gfn;

	if (!vpa->dirty || !vpa->pinned_addr)
		return;
	gfn = vpa->gpa >> PAGE_SHIFT;
	if (gfn < memslot->base_gfn ||
	    gfn >= memslot->base_gfn + memslot->npages)
		return;

	vpa->dirty = false;
	if (map)
		__set_bit_le(gfn - memslot->base_gfn, map);
}