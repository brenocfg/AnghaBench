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
struct mtk_vcodec_ctx {int dummy; } ;
struct mtk_q_data {unsigned int* sizeimage; TYPE_1__* fmt; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int num_planes; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_q_data* mtk_venc_get_q_data (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 
 struct mtk_vcodec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int vb2ops_venc_queue_setup(struct vb2_queue *vq,
				   unsigned int *nbuffers,
				   unsigned int *nplanes,
				   unsigned int sizes[],
				   struct device *alloc_devs[])
{
	struct mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vq);
	struct mtk_q_data *q_data;
	unsigned int i;

	q_data = mtk_venc_get_q_data(ctx, vq->type);

	if (q_data == NULL)
		return -EINVAL;

	if (*nplanes) {
		for (i = 0; i < *nplanes; i++)
			if (sizes[i] < q_data->sizeimage[i])
				return -EINVAL;
	} else {
		*nplanes = q_data->fmt->num_planes;
		for (i = 0; i < *nplanes; i++)
			sizes[i] = q_data->sizeimage[i];
	}

	return 0;
}