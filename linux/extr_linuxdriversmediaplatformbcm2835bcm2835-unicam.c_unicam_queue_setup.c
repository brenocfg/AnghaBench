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
struct vb2_queue {unsigned int num_buffers; } ;
struct TYPE_4__ {unsigned int sizeimage; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct TYPE_5__ {TYPE_3__ fmt; } ;
struct unicam_device {TYPE_2__ v_fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  unicam_err (struct unicam_device*,char*,unsigned int,unsigned int) ; 
 struct unicam_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int unicam_queue_setup(struct vb2_queue *vq,
			      unsigned int *nbuffers,
			      unsigned int *nplanes,
			      unsigned int sizes[],
			      struct device *alloc_devs[])
{
	struct unicam_device *dev = vb2_get_drv_priv(vq);
	unsigned int size = dev->v_fmt.fmt.pix.sizeimage;

	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	if (*nplanes) {
		if (sizes[0] < size) {
			unicam_err(dev, "sizes[0] %i < size %u\n", sizes[0],
				   size);
			return -EINVAL;
		}
		size = sizes[0];
	}

	*nplanes = 1;
	sizes[0] = size;

	return 0;
}