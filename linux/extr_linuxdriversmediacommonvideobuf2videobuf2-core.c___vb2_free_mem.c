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
struct vb2_queue {unsigned int num_buffers; scalar_t__ memory; struct vb2_buffer** bufs; } ;
struct vb2_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ VB2_MEMORY_DMABUF ; 
 scalar_t__ VB2_MEMORY_MMAP ; 
 int /*<<< orphan*/  __vb2_buf_dmabuf_put (struct vb2_buffer*) ; 
 int /*<<< orphan*/  __vb2_buf_mem_free (struct vb2_buffer*) ; 
 int /*<<< orphan*/  __vb2_buf_userptr_put (struct vb2_buffer*) ; 

__attribute__((used)) static void __vb2_free_mem(struct vb2_queue *q, unsigned int buffers)
{
	unsigned int buffer;
	struct vb2_buffer *vb;

	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		vb = q->bufs[buffer];
		if (!vb)
			continue;

		/* Free MMAP buffers or release USERPTR buffers */
		if (q->memory == VB2_MEMORY_MMAP)
			__vb2_buf_mem_free(vb);
		else if (q->memory == VB2_MEMORY_DMABUF)
			__vb2_buf_dmabuf_put(vb);
		else
			__vb2_buf_userptr_put(vb);
	}
}