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
struct vivid_dev {int* std_cap; size_t input; } ;
struct vb2_queue {scalar_t__ type; unsigned int num_buffers; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ; 
 int V4L2_STD_525_60 ; 
 struct vivid_dev* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vivid_is_sdtv_cap (struct vivid_dev*) ; 

__attribute__((used)) static int vbi_cap_queue_setup(struct vb2_queue *vq,
		       unsigned *nbuffers, unsigned *nplanes,
		       unsigned sizes[], struct device *alloc_devs[])
{
	struct vivid_dev *dev = vb2_get_drv_priv(vq);
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;
	unsigned size = vq->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ?
		36 * sizeof(struct v4l2_sliced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

	if (!vivid_is_sdtv_cap(dev))
		return -EINVAL;

	sizes[0] = size;

	if (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = 1;
	return 0;
}