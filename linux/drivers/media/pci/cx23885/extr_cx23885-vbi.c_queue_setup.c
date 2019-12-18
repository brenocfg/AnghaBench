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
struct vb2_queue {struct cx23885_dev* drv_priv; } ;
struct device {int dummy; } ;
struct cx23885_dev {int tvnorm; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 unsigned int VBI_LINE_LENGTH ; 
 unsigned int VBI_NTSC_LINE_COUNT ; 
 unsigned int VBI_PAL_LINE_COUNT ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *q,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct cx23885_dev *dev = q->drv_priv;
	unsigned lines = VBI_PAL_LINE_COUNT;

	if (dev->tvnorm & V4L2_STD_525_60)
		lines = VBI_NTSC_LINE_COUNT;
	*num_planes = 1;
	sizes[0] = lines * VBI_LINE_LENGTH * 2;
	return 0;
}