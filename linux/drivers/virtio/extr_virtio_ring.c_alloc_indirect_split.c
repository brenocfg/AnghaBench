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
struct vring_desc {int /*<<< orphan*/  next; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __GFP_HIGHMEM ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,unsigned int) ; 
 struct vring_desc* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vring_desc *alloc_indirect_split(struct virtqueue *_vq,
					       unsigned int total_sg,
					       gfp_t gfp)
{
	struct vring_desc *desc;
	unsigned int i;

	/*
	 * We require lowmem mappings for the descriptors because
	 * otherwise virt_to_phys will give us bogus addresses in the
	 * virtqueue.
	 */
	gfp &= ~__GFP_HIGHMEM;

	desc = kmalloc_array(total_sg, sizeof(struct vring_desc), gfp);
	if (!desc)
		return NULL;

	for (i = 0; i < total_sg; i++)
		desc[i].next = cpu_to_virtio16(_vq->vdev, i + 1);
	return desc;
}