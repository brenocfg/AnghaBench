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
struct vb2_queue {unsigned int num_buffers; } ;
struct tw68_dev {int width; int height; TYPE_1__* fmt; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int tw68_buffer_count (unsigned int,unsigned int) ; 
 struct tw68_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int tw68_queue_setup(struct vb2_queue *q,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct tw68_dev *dev = vb2_get_drv_priv(q);
	unsigned tot_bufs = q->num_buffers + *num_buffers;
	unsigned size = (dev->fmt->depth * dev->width * dev->height) >> 3;

	if (tot_bufs < 2)
		tot_bufs = 2;
	tot_bufs = tw68_buffer_count(size, tot_bufs);
	*num_buffers = tot_bufs - q->num_buffers;
	/*
	 * We allow create_bufs, but only if the sizeimage is >= as the
	 * current sizeimage. The tw68_buffer_count calculation becomes quite
	 * difficult otherwise.
	 */
	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;
	*num_planes = 1;
	sizes[0] = size;

	return 0;
}