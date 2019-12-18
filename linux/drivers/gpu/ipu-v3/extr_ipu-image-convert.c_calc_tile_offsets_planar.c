#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipu_image_pixfmt {int uv_width_dec; int uv_height_dec; scalar_t__ uv_swapped; scalar_t__ uv_packed; } ;
struct ipu_image_convert_priv {TYPE_4__* ipu; } ;
struct TYPE_5__ {int height; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct ipu_image_convert_image {int stride; unsigned int num_rows; unsigned int num_cols; scalar_t__ type; TYPE_3__* tile; TYPE_2__ base; struct ipu_image_pixfmt* fmt; } ;
struct ipu_image_convert_ctx {struct ipu_image_convert_chan* chan; } ;
struct ipu_image_convert_chan {int /*<<< orphan*/  ic_task; struct ipu_image_convert_priv* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int top; int left; int offset; int u_off; int v_off; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IMAGE_CONVERT_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ipu_image_convert_ctx*,char*,unsigned int,unsigned int,int,int,int) ; 

__attribute__((used)) static int calc_tile_offsets_planar(struct ipu_image_convert_ctx *ctx,
				    struct ipu_image_convert_image *image)
{
	struct ipu_image_convert_chan *chan = ctx->chan;
	struct ipu_image_convert_priv *priv = chan->priv;
	const struct ipu_image_pixfmt *fmt = image->fmt;
	unsigned int row, col, tile = 0;
	u32 H, top, y_stride, uv_stride;
	u32 uv_row_off, uv_col_off, uv_off, u_off, v_off, tmp;
	u32 y_row_off, y_col_off, y_off;
	u32 y_size, uv_size;

	/* setup some convenience vars */
	H = image->base.pix.height;

	y_stride = image->stride;
	uv_stride = y_stride / fmt->uv_width_dec;
	if (fmt->uv_packed)
		uv_stride *= 2;

	y_size = H * y_stride;
	uv_size = y_size / (fmt->uv_width_dec * fmt->uv_height_dec);

	for (row = 0; row < image->num_rows; row++) {
		top = image->tile[tile].top;
		y_row_off = top * y_stride;
		uv_row_off = (top * uv_stride) / fmt->uv_height_dec;

		for (col = 0; col < image->num_cols; col++) {
			y_col_off = image->tile[tile].left;
			uv_col_off = y_col_off / fmt->uv_width_dec;
			if (fmt->uv_packed)
				uv_col_off *= 2;

			y_off = y_row_off + y_col_off;
			uv_off = uv_row_off + uv_col_off;

			u_off = y_size - y_off + uv_off;
			v_off = (fmt->uv_packed) ? 0 : u_off + uv_size;
			if (fmt->uv_swapped) {
				tmp = u_off;
				u_off = v_off;
				v_off = tmp;
			}

			image->tile[tile].offset = y_off;
			image->tile[tile].u_off = u_off;
			image->tile[tile++].v_off = v_off;

			if ((y_off & 0x7) || (u_off & 0x7) || (v_off & 0x7)) {
				dev_err(priv->ipu->dev,
					"task %u: ctx %p: %s@[%d,%d]: "
					"y_off %08x, u_off %08x, v_off %08x\n",
					chan->ic_task, ctx,
					image->type == IMAGE_CONVERT_IN ?
					"Input" : "Output", row, col,
					y_off, u_off, v_off);
				return -EINVAL;
			}
		}
	}

	return 0;
}