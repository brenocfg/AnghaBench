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
struct vb2_queue {struct vb2_buffer** bufs; } ;
struct TYPE_2__ {unsigned long offset; } ;
struct vb2_plane {unsigned long length; TYPE_1__ m; } ;
struct vb2_buffer {int index; int num_planes; struct vb2_plane* planes; struct vb2_queue* vb2_queue; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,unsigned int,unsigned long) ; 

__attribute__((used)) static void __setup_offsets(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	unsigned int plane;
	unsigned long off = 0;

	if (vb->index) {
		struct vb2_buffer *prev = q->bufs[vb->index - 1];
		struct vb2_plane *p = &prev->planes[prev->num_planes - 1];

		off = PAGE_ALIGN(p->m.offset + p->length);
	}

	for (plane = 0; plane < vb->num_planes; ++plane) {
		vb->planes[plane].m.offset = off;

		dprintk(3, "buffer %d, plane %d offset 0x%08lx\n",
				vb->index, plane, off);

		off += vb->planes[plane].length;
		off = PAGE_ALIGN(off);
	}
}