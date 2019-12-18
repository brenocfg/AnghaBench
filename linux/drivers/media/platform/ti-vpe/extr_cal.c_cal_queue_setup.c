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
struct device {int dummy; } ;
struct TYPE_6__ {unsigned int sizeimage; } ;
struct TYPE_5__ {TYPE_3__ pix; } ;
struct TYPE_4__ {TYPE_2__ fmt; } ;
struct cal_ctx {TYPE_1__ v_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,unsigned int,unsigned int) ; 
 struct cal_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int cal_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vq);
	unsigned size = ctx->v_fmt.fmt.pix.sizeimage;

	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	if (*nplanes) {
		if (sizes[0] < size)
			return -EINVAL;
		size = sizes[0];
	}

	*nplanes = 1;
	sizes[0] = size;

	ctx_dbg(3, ctx, "nbuffers=%d, size=%d\n", *nbuffers, sizes[0]);

	return 0;
}