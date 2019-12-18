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
struct solo_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MIN_VID_BUFFERS ; 
 unsigned int solo_image_size (struct solo_dev*) ; 
 struct solo_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int solo_queue_setup(struct vb2_queue *q,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct solo_dev *solo_dev = vb2_get_drv_priv(q);

	sizes[0] = solo_image_size(solo_dev);
	*num_planes = 1;

	if (*num_buffers < MIN_VID_BUFFERS)
		*num_buffers = MIN_VID_BUFFERS;

	return 0;
}