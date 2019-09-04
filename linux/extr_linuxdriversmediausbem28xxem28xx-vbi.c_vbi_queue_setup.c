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
struct em28xx_v4l2 {int vbi_width; int vbi_height; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct em28xx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int vbi_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct em28xx *dev = vb2_get_drv_priv(vq);
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	unsigned long size = v4l2->vbi_width * v4l2->vbi_height * 2;

	if (*nbuffers < 2)
		*nbuffers = 2;

	if (*nplanes) {
		if (sizes[0] < size)
			return -EINVAL;
		size = sizes[0];
	}

	*nplanes = 1;
	sizes[0] = size;

	return 0;
}