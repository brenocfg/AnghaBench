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
struct emmaprp_q_data {int width; int height; TYPE_1__* fmt; } ;
struct emmaprp_ctx {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int MEM2MEM_VID_MEM_LIMIT ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct emmaprp_q_data* get_q_data (struct emmaprp_ctx*,int /*<<< orphan*/ ) ; 
 struct emmaprp_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int emmaprp_queue_setup(struct vb2_queue *vq,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[], struct device *alloc_devs[])
{
	struct emmaprp_ctx *ctx = vb2_get_drv_priv(vq);
	struct emmaprp_q_data *q_data;
	unsigned int size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	if (q_data->fmt->fourcc == V4L2_PIX_FMT_YUV420)
		size = q_data->width * q_data->height * 3 / 2;
	else
		size = q_data->width * q_data->height * 2;

	while (size * count > MEM2MEM_VID_MEM_LIMIT)
		(count)--;

	*nplanes = 1;
	*nbuffers = count;
	sizes[0] = size;

	dprintk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	return 0;
}