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
struct vring_packed_desc {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __GFP_HIGHMEM ; 
 struct vring_packed_desc* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vring_packed_desc *alloc_indirect_packed(unsigned int total_sg,
						       gfp_t gfp)
{
	struct vring_packed_desc *desc;

	/*
	 * We require lowmem mappings for the descriptors because
	 * otherwise virt_to_phys will give us bogus addresses in the
	 * virtqueue.
	 */
	gfp &= ~__GFP_HIGHMEM;

	desc = kmalloc_array(total_sg, sizeof(struct vring_packed_desc), gfp);

	return desc;
}