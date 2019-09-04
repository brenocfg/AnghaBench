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
struct TYPE_3__ {unsigned int sizeimage; } ;
struct vpbe_layer {TYPE_1__ pix_fmt; TYPE_2__* disp_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct vb2_queue {scalar_t__ num_buffers; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VPBE_DEFAULT_NUM_BUFS ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int
vpbe_buffer_queue_setup(struct vb2_queue *vq,
			unsigned int *nbuffers, unsigned int *nplanes,
			unsigned int sizes[], struct device *alloc_devs[])

{
	/* Get the file handle object and layer object */
	struct vpbe_layer *layer = vb2_get_drv_priv(vq);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_buffer_setup\n");

	/* Store number of buffers allocated in numbuffer member */
	if (vq->num_buffers + *nbuffers < VPBE_DEFAULT_NUM_BUFS)
		*nbuffers = VPBE_DEFAULT_NUM_BUFS - vq->num_buffers;

	if (*nplanes)
		return sizes[0] < layer->pix_fmt.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = layer->pix_fmt.sizeimage;

	return 0;
}