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
struct tw686x_video_channel {int width; int height; TYPE_1__* format; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 struct tw686x_video_channel* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int tw686x_queue_setup(struct vb2_queue *vq,
			      unsigned int *nbuffers, unsigned int *nplanes,
			      unsigned int sizes[], struct device *alloc_devs[])
{
	struct tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	unsigned int szimage =
		(vc->width * vc->height * vc->format->depth) >> 3;

	/*
	 * Let's request at least three buffers: two for the
	 * DMA engine and one for userspace.
	 */
	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	if (*nplanes) {
		if (*nplanes != 1 || sizes[0] < szimage)
			return -EINVAL;
		return 0;
	}

	sizes[0] = szimage;
	*nplanes = 1;
	return 0;
}