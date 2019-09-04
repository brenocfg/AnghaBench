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
struct vb2_queue {int /*<<< orphan*/  num_buffers; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_device {unsigned int sizeimage; int /*<<< orphan*/  parent; } ;
struct sh_mobile_ceu_dev {scalar_t__ video_limit; scalar_t__ buf_total; scalar_t__ sequence; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_ALIGN (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct soc_camera_device* soc_camera_from_vb2q (struct vb2_queue*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_ceu_videobuf_setup(struct vb2_queue *vq,
			unsigned int *count, unsigned int *num_planes,
			unsigned int sizes[], struct device *alloc_devs[])
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vq);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;

	if (!vq->num_buffers)
		pcdev->sequence = 0;

	if (!*count)
		*count = 2;

	/* Called from VIDIOC_REQBUFS or in compatibility mode */
	if (!*num_planes)
		sizes[0] = icd->sizeimage;
	else if (sizes[0] < icd->sizeimage)
		return -EINVAL;

	/* If *num_planes != 0, we have already verified *count. */
	if (pcdev->video_limit) {
		size_t size = PAGE_ALIGN(sizes[0]) * *count;

		if (size + pcdev->buf_total > pcdev->video_limit)
			*count = (pcdev->video_limit - pcdev->buf_total) /
				PAGE_ALIGN(sizes[0]);
	}

	*num_planes = 1;

	dev_dbg(icd->parent, "count=%d, size=%u\n", *count, sizes[0]);

	return 0;
}