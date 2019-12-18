#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vsp1_video {TYPE_1__* rwpf; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {unsigned int num_planes; TYPE_2__* plane_fmt; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned int sizeimage; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane format; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vsp1_video* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int
vsp1_video_queue_setup(struct vb2_queue *vq,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct vsp1_video *video = vb2_get_drv_priv(vq);
	const struct v4l2_pix_format_mplane *format = &video->rwpf->format;
	unsigned int i;

	if (*nplanes) {
		if (*nplanes != format->num_planes)
			return -EINVAL;

		for (i = 0; i < *nplanes; i++)
			if (sizes[i] < format->plane_fmt[i].sizeimage)
				return -EINVAL;
		return 0;
	}

	*nplanes = format->num_planes;

	for (i = 0; i < format->num_planes; ++i)
		sizes[i] = format->plane_fmt[i].sizeimage;

	return 0;
}