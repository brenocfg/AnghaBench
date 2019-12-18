#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {TYPE_2__* planes; } ;
struct vb2_plane {int /*<<< orphan*/  data_offset; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  length; int /*<<< orphan*/  m; } ;
struct vb2_buffer {unsigned int num_planes; TYPE_1__* vb2_queue; scalar_t__ timestamp; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_offset; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  length; int /*<<< orphan*/  m; } ;
struct TYPE_3__ {scalar_t__ memory; int /*<<< orphan*/  copy_timestamp; } ;

/* Variables and functions */
 scalar_t__ VB2_MEMORY_MMAP ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static int __fill_vb2_buffer(struct vb2_buffer *vb, struct vb2_plane *planes)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	unsigned int plane;

	if (!vb->vb2_queue->copy_timestamp)
		vb->timestamp = 0;

	for (plane = 0; plane < vb->num_planes; ++plane) {
		if (vb->vb2_queue->memory != VB2_MEMORY_MMAP) {
			planes[plane].m = vbuf->planes[plane].m;
			planes[plane].length = vbuf->planes[plane].length;
		}
		planes[plane].bytesused = vbuf->planes[plane].bytesused;
		planes[plane].data_offset = vbuf->planes[plane].data_offset;
	}
	return 0;
}