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
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int H264_VLC_BUF_SIZE ; 

__attribute__((used)) static int tw5864_queue_setup(struct vb2_queue *q, unsigned int *num_buffers,
			      unsigned int *num_planes, unsigned int sizes[],
			      struct device *alloc_ctxs[])
{
	if (*num_planes)
		return sizes[0] < H264_VLC_BUF_SIZE ? -EINVAL : 0;

	sizes[0] = H264_VLC_BUF_SIZE;
	*num_planes = 1;

	return 0;
}