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
struct vb2_buffer {int num_planes; } ;
struct mtk_jpeg_fb {int /*<<< orphan*/ * plane_addr; } ;
struct mtk_jpeg_dec_param {int comp_num; scalar_t__* comp_size; } ;
struct mtk_jpeg_ctx {TYPE_1__* jpeg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int) ; 

__attribute__((used)) static int mtk_jpeg_set_dec_dst(struct mtk_jpeg_ctx *ctx,
				struct mtk_jpeg_dec_param *param,
				struct vb2_buffer *dst_buf,
				struct mtk_jpeg_fb *fb)
{
	int i;

	if (param->comp_num != dst_buf->num_planes) {
		dev_err(ctx->jpeg->dev, "plane number mismatch (%u != %u)\n",
			param->comp_num, dst_buf->num_planes);
		return -EINVAL;
	}

	for (i = 0; i < dst_buf->num_planes; i++) {
		if (vb2_plane_size(dst_buf, i) < param->comp_size[i]) {
			dev_err(ctx->jpeg->dev,
				"buffer size is underflow (%lu < %u)\n",
				vb2_plane_size(dst_buf, 0),
				param->comp_size[i]);
			return -EINVAL;
		}
		fb->plane_addr[i] = vb2_dma_contig_plane_dma_addr(dst_buf, i);
	}

	return 0;
}