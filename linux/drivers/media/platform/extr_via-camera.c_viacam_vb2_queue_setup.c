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
struct TYPE_2__ {int sizeimage; } ;
struct via_camera {TYPE_1__ user_format; } ;
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct via_camera* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int viacam_vb2_queue_setup(struct vb2_queue *vq,
				  unsigned int *nbufs,
				  unsigned int *num_planes, unsigned int sizes[],
				  struct device *alloc_devs[])
{
	struct via_camera *cam = vb2_get_drv_priv(vq);
	int size = cam->user_format.sizeimage;

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	return 0;
}