#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
struct coda_q_data {unsigned int sizeimage; } ;
struct coda_ctx {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  coda_debug ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 struct coda_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int coda_queue_setup(struct vb2_queue *vq,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[], struct device *alloc_devs[])
{
	struct coda_ctx *ctx = vb2_get_drv_priv(vq);
	struct coda_q_data *q_data;
	unsigned int size;

	q_data = get_q_data(ctx, vq->type);
	size = q_data->sizeimage;

	*nplanes = 1;
	sizes[0] = size;

	v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
		 "get %d buffer(s) of size %d each.\n", *nbuffers, size);

	return 0;
}