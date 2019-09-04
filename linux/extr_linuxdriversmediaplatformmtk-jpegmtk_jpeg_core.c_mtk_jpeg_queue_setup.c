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
struct vb2_queue {int type; } ;
struct mtk_jpeg_q_data {unsigned int* sizeimage; TYPE_1__* fmt; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct mtk_jpeg_ctx {struct mtk_jpeg_dev* jpeg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int colplanes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 struct mtk_jpeg_q_data* mtk_jpeg_get_q_data (struct mtk_jpeg_ctx*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,unsigned int) ; 
 struct mtk_jpeg_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int mtk_jpeg_queue_setup(struct vb2_queue *q,
				unsigned int *num_buffers,
				unsigned int *num_planes,
				unsigned int sizes[],
				struct device *alloc_ctxs[])
{
	struct mtk_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	struct mtk_jpeg_q_data *q_data = NULL;
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	int i;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) buf_req count=%u\n",
		 q->type, *num_buffers);

	q_data = mtk_jpeg_get_q_data(ctx, q->type);
	if (!q_data)
		return -EINVAL;

	*num_planes = q_data->fmt->colplanes;
	for (i = 0; i < q_data->fmt->colplanes; i++) {
		sizes[i] = q_data->sizeimage[i];
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "sizeimage[%d]=%u\n",
			 i, sizes[i]);
	}

	return 0;
}