#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {unsigned int num_planes; TYPE_3__* plane_fmt; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct camss_video {TYPE_2__ active_fmt; } ;
struct TYPE_6__ {unsigned int sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 struct camss_video* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int video_queue_setup(struct vb2_queue *q,
	unsigned int *num_buffers, unsigned int *num_planes,
	unsigned int sizes[], struct device *alloc_devs[])
{
	struct camss_video *video = vb2_get_drv_priv(q);
	const struct v4l2_pix_format_mplane *format =
						&video->active_fmt.fmt.pix_mp;
	unsigned int i;

	if (*num_planes) {
		if (*num_planes != format->num_planes)
			return -EINVAL;

		for (i = 0; i < *num_planes; i++)
			if (sizes[i] < format->plane_fmt[i].sizeimage)
				return -EINVAL;

		return 0;
	}

	*num_planes = format->num_planes;

	for (i = 0; i < *num_planes; i++)
		sizes[i] = format->plane_fmt[i].sizeimage;

	return 0;
}