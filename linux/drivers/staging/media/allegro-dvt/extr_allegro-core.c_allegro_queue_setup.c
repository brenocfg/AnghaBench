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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct allegro_channel {unsigned int sizeimage_raw; unsigned int sizeimage_encoded; struct allegro_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,unsigned int) ; 
 struct allegro_channel* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int allegro_queue_setup(struct vb2_queue *vq,
			       unsigned int *nbuffers, unsigned int *nplanes,
			       unsigned int sizes[],
			       struct device *alloc_devs[])
{
	struct allegro_channel *channel = vb2_get_drv_priv(vq);
	struct allegro_dev *dev = channel->dev;

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "%s: queue setup[%s]: nplanes = %d\n",
		 V4L2_TYPE_IS_OUTPUT(vq->type) ? "output" : "capture",
		 *nplanes == 0 ? "REQBUFS" : "CREATE_BUFS", *nplanes);

	if (*nplanes != 0) {
		if (V4L2_TYPE_IS_OUTPUT(vq->type)) {
			if (sizes[0] < channel->sizeimage_raw)
				return -EINVAL;
		} else {
			if (sizes[0] < channel->sizeimage_encoded)
				return -EINVAL;
		}
	} else {
		*nplanes = 1;
		if (V4L2_TYPE_IS_OUTPUT(vq->type))
			sizes[0] = channel->sizeimage_raw;
		else
			sizes[0] = channel->sizeimage_encoded;
	}

	return 0;
}