#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_buffer {unsigned int num_planes; TYPE_3__* planes; } ;
struct TYPE_5__ {TYPE_1__* planes; } ;
struct v4l2_buffer {scalar_t__ memory; unsigned int length; unsigned int bytesused; TYPE_2__ m; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {unsigned int length; } ;
struct TYPE_4__ {unsigned int length; int bytesused; unsigned int data_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ VB2_MEMORY_DMABUF ; 
 scalar_t__ VB2_MEMORY_USERPTR ; 

__attribute__((used)) static int __verify_length(struct vb2_buffer *vb, const struct v4l2_buffer *b)
{
	unsigned int length;
	unsigned int bytesused;
	unsigned int plane;

	if (!V4L2_TYPE_IS_OUTPUT(b->type))
		return 0;

	if (V4L2_TYPE_IS_MULTIPLANAR(b->type)) {
		for (plane = 0; plane < vb->num_planes; ++plane) {
			length = (b->memory == VB2_MEMORY_USERPTR ||
				  b->memory == VB2_MEMORY_DMABUF)
			       ? b->m.planes[plane].length
				: vb->planes[plane].length;
			bytesused = b->m.planes[plane].bytesused
				  ? b->m.planes[plane].bytesused : length;

			if (b->m.planes[plane].bytesused > length)
				return -EINVAL;

			if (b->m.planes[plane].data_offset > 0 &&
			    b->m.planes[plane].data_offset >= bytesused)
				return -EINVAL;
		}
	} else {
		length = (b->memory == VB2_MEMORY_USERPTR)
			? b->length : vb->planes[0].length;

		if (b->bytesused > length)
			return -EINVAL;
	}

	return 0;
}