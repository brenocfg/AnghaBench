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
struct pxp_q_data {unsigned int sizeimage; } ;
struct pxp_ctx {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct pxp_q_data* get_q_data (struct pxp_ctx*,int /*<<< orphan*/ ) ; 
 struct pxp_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int pxp_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct pxp_ctx *ctx = vb2_get_drv_priv(vq);
	struct pxp_q_data *q_data;
	unsigned int size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->sizeimage;

	*nbuffers = count;

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dprintk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	return 0;
}