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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {unsigned int sizeimage; } ;
struct ipu_csc_scaler_q_data {TYPE_1__ cur_fmt; } ;
struct ipu_csc_scaler_ctx {TYPE_2__* priv; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct ipu_csc_scaler_q_data* get_q_data (struct ipu_csc_scaler_ctx*,int /*<<< orphan*/ ) ; 
 struct ipu_csc_scaler_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int ipu_csc_scaler_queue_setup(struct vb2_queue *vq,
				      unsigned int *nbuffers,
				      unsigned int *nplanes,
				      unsigned int sizes[],
				      struct device *alloc_devs[])
{
	struct ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(vq);
	struct ipu_csc_scaler_q_data *q_data;
	unsigned int size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->cur_fmt.sizeimage;

	*nbuffers = count;

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dev_dbg(ctx->priv->dev, "get %d buffer(s) of size %d each.\n",
		count, size);

	return 0;
}