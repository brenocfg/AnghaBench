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
struct vnic_dev_ring {int base_align; int desc_count; int desc_size; int size; int size_unaligned; } ;

/* Variables and functions */
 void* ALIGN (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int vnic_dev_desc_ring_size(struct vnic_dev_ring *ring,
	unsigned int desc_count, unsigned int desc_size)
{
	/* The base address of the desc rings must be 512 byte aligned.
	 * Descriptor count is aligned to groups of 32 descriptors.  A
	 * count of 0 means the maximum 4096 descriptors.  Descriptor
	 * size is aligned to 16 bytes.
	 */

	unsigned int count_align = 32;
	unsigned int desc_align = 16;

	ring->base_align = 512;

	if (desc_count == 0)
		desc_count = 4096;

	ring->desc_count = ALIGN(desc_count, count_align);

	ring->desc_size = ALIGN(desc_size, desc_align);

	ring->size = ring->desc_count * ring->desc_size;
	ring->size_unaligned = ring->size + ring->base_align;

	return ring->size_unaligned;
}