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
struct vb2_queue {struct cx25821_channel* drv_priv; } ;
struct device {int dummy; } ;
struct cx25821_channel {int width; int height; TYPE_1__* fmt; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cx25821_queue_setup(struct vb2_queue *q,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct cx25821_channel *chan = q->drv_priv;
	unsigned size = (chan->fmt->depth * chan->width * chan->height) >> 3;

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	return 0;
}