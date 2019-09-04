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
struct vb2_buffer {TYPE_2__* vb2_queue; } ;
struct mtk_jpeg_q_data {int /*<<< orphan*/ * sizeimage; TYPE_1__* fmt; } ;
struct mtk_jpeg_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int colplanes; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_jpeg_q_data* mtk_jpeg_get_q_data (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 struct mtk_jpeg_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_jpeg_buf_prepare(struct vb2_buffer *vb)
{
	struct mtk_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct mtk_jpeg_q_data *q_data = NULL;
	int i;

	q_data = mtk_jpeg_get_q_data(ctx, vb->vb2_queue->type);
	if (!q_data)
		return -EINVAL;

	for (i = 0; i < q_data->fmt->colplanes; i++)
		vb2_set_plane_payload(vb, i, q_data->sizeimage[i]);

	return 0;
}