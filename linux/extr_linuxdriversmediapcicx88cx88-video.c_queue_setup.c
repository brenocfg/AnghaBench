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
struct vb2_queue {struct cx8800_dev* drv_priv; } ;
struct device {int dummy; } ;
struct cx88_core {int width; int height; } ;
struct cx8800_dev {TYPE_1__* fmt; struct cx88_core* core; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */

__attribute__((used)) static int queue_setup(struct vb2_queue *q,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct cx8800_dev *dev = q->drv_priv;
	struct cx88_core *core = dev->core;

	*num_planes = 1;
	sizes[0] = (dev->fmt->depth * core->width * core->height) >> 3;
	return 0;
}