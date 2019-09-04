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
struct vb2_queue {scalar_t__ memory; } ;
struct vb2_buffer {scalar_t__ state; unsigned int num_planes; TYPE_1__* planes; struct vb2_queue* vb2_queue; } ;
struct TYPE_2__ {scalar_t__ dbuf_mapped; int /*<<< orphan*/  mem_priv; } ;

/* Variables and functions */
 scalar_t__ VB2_BUF_STATE_DEQUEUED ; 
 scalar_t__ VB2_MEMORY_DMABUF ; 
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_dmabuf ; 

__attribute__((used)) static void __vb2_dqbuf(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	unsigned int i;

	/* nothing to do if the buffer is already dequeued */
	if (vb->state == VB2_BUF_STATE_DEQUEUED)
		return;

	vb->state = VB2_BUF_STATE_DEQUEUED;

	/* unmap DMABUF buffer */
	if (q->memory == VB2_MEMORY_DMABUF)
		for (i = 0; i < vb->num_planes; ++i) {
			if (!vb->planes[i].dbuf_mapped)
				continue;
			call_void_memop(vb, unmap_dmabuf, vb->planes[i].mem_priv);
			vb->planes[i].dbuf_mapped = 0;
		}
}