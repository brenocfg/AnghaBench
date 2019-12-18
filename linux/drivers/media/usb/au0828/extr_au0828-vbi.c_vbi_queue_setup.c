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
struct au0828_dev {int vbi_width; int vbi_height; } ;

/* Variables and functions */
 int EINVAL ; 
 struct au0828_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int vbi_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct au0828_dev *dev = vb2_get_drv_priv(vq);
	unsigned long size = dev->vbi_width * dev->vbi_height * 2;

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;
	return 0;
}