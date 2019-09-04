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
struct vb2_buffer {unsigned int num_planes; int /*<<< orphan*/ * planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vb2_plane_dmabuf_put (struct vb2_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vb2_buf_dmabuf_put(struct vb2_buffer *vb)
{
	unsigned int plane;

	for (plane = 0; plane < vb->num_planes; ++plane)
		__vb2_plane_dmabuf_put(vb, &vb->planes[plane]);
}