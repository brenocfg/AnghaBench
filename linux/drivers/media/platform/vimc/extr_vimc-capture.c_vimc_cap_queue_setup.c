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
struct TYPE_2__ {unsigned int sizeimage; } ;
struct vimc_cap_device {TYPE_1__ format; } ;
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vimc_cap_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int vimc_cap_queue_setup(struct vb2_queue *vq, unsigned int *nbuffers,
				unsigned int *nplanes, unsigned int sizes[],
				struct device *alloc_devs[])
{
	struct vimc_cap_device *vcap = vb2_get_drv_priv(vq);

	if (*nplanes)
		return sizes[0] < vcap->format.sizeimage ? -EINVAL : 0;
	/* We don't support multiplanes for now */
	*nplanes = 1;
	sizes[0] = vcap->format.sizeimage;

	return 0;
}