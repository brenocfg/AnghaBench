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
struct TYPE_4__ {unsigned int sizeimage; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct stm32_dcmi {int /*<<< orphan*/  dev; TYPE_3__ fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct stm32_dcmi* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int dcmi_queue_setup(struct vb2_queue *vq,
			    unsigned int *nbuffers,
			    unsigned int *nplanes,
			    unsigned int sizes[],
			    struct device *alloc_devs[])
{
	struct stm32_dcmi *dcmi = vb2_get_drv_priv(vq);
	unsigned int size;

	size = dcmi->fmt.fmt.pix.sizeimage;

	/* Make sure the image size is large enough */
	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dev_dbg(dcmi->dev, "Setup queue, count=%d, size=%d\n",
		*nbuffers, size);

	return 0;
}