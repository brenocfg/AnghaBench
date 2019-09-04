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
struct mtk_vcodec_ctx {int dummy; } ;
struct mtk_q_data {scalar_t__* sizeimage; TYPE_1__* fmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int num_planes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int,scalar_t__,scalar_t__) ; 
 struct mtk_q_data* mtk_venc_get_q_data (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 
 struct mtk_vcodec_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int) ; 

__attribute__((used)) static int vb2ops_venc_buf_prepare(struct vb2_buffer *vb)
{
	struct mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct mtk_q_data *q_data;
	int i;

	q_data = mtk_venc_get_q_data(ctx, vb->vb2_queue->type);

	for (i = 0; i < q_data->fmt->num_planes; i++) {
		if (vb2_plane_size(vb, i) < q_data->sizeimage[i]) {
			mtk_v4l2_err("data will not fit into plane %d (%lu < %d)",
				i, vb2_plane_size(vb, i),
				q_data->sizeimage[i]);
			return -EINVAL;
		}
	}

	return 0;
}