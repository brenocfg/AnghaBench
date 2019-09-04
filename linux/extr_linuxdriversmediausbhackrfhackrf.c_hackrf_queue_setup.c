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
struct vb2_queue {unsigned int num_buffers; } ;
struct hackrf_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  buffersize; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 struct hackrf_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int hackrf_queue_setup(struct vb2_queue *vq,
		unsigned int *nbuffers,
		unsigned int *nplanes, unsigned int sizes[], struct device *alloc_devs[])
{
	struct hackrf_dev *dev = vb2_get_drv_priv(vq);

	dev_dbg(dev->dev, "nbuffers=%d\n", *nbuffers);

	/* Need at least 8 buffers */
	if (vq->num_buffers + *nbuffers < 8)
		*nbuffers = 8 - vq->num_buffers;
	*nplanes = 1;
	sizes[0] = PAGE_ALIGN(dev->buffersize);

	dev_dbg(dev->dev, "nbuffers=%d sizes[0]=%d\n", *nbuffers, sizes[0]);
	return 0;
}