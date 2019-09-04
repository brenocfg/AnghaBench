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
struct vb2_queue {scalar_t__ memory; struct vb2_buffer** bufs; } ;
struct vb2_buffer {int dummy; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ VB2_MEMORY_MMAP ; 
 int __find_plane_by_offset (struct vb2_queue*,unsigned long,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 void* vb2_plane_vaddr (struct vb2_buffer*,unsigned int) ; 

unsigned long vb2_get_unmapped_area(struct vb2_queue *q,
				    unsigned long addr,
				    unsigned long len,
				    unsigned long pgoff,
				    unsigned long flags)
{
	unsigned long off = pgoff << PAGE_SHIFT;
	struct vb2_buffer *vb;
	unsigned int buffer, plane;
	void *vaddr;
	int ret;

	if (q->memory != VB2_MEMORY_MMAP) {
		dprintk(1, "queue is not currently set up for mmap\n");
		return -EINVAL;
	}

	/*
	 * Find the plane corresponding to the offset passed by userspace.
	 */
	ret = __find_plane_by_offset(q, off, &buffer, &plane);
	if (ret)
		return ret;

	vb = q->bufs[buffer];

	vaddr = vb2_plane_vaddr(vb, plane);
	return vaddr ? (unsigned long)vaddr : -EINVAL;
}