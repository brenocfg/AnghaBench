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
struct vb2_queue {scalar_t__ num_buffers; } ;
struct TYPE_2__ {int sizeimage; } ;
struct omap_vout_device {TYPE_1__ pix; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VRFB_NUM_BUFS ; 
 scalar_t__ is_rotation_enabled (struct omap_vout_device*) ; 
 struct omap_vout_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int omap_vout_vb2_queue_setup(struct vb2_queue *vq,
				     unsigned int *nbufs,
				     unsigned int *num_planes, unsigned int sizes[],
				     struct device *alloc_devs[])
{
	struct omap_vout_device *vout = vb2_get_drv_priv(vq);
	int size = vout->pix.sizeimage;

	if (is_rotation_enabled(vout) && vq->num_buffers + *nbufs > VRFB_NUM_BUFS) {
		*nbufs = VRFB_NUM_BUFS - vq->num_buffers;
		if (*nbufs == 0)
			return -EINVAL;
	}

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	return 0;
}