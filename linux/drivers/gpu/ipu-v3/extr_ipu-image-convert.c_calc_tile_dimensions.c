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
struct ipu_image_tile {int size; int height; int width; int stride; int rot_stride; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct ipu_image_convert_priv {TYPE_2__* ipu; } ;
struct ipu_image_convert_image {scalar_t__ type; unsigned int num_cols; TYPE_1__* fmt; struct ipu_image_tile* tile; } ;
struct ipu_image_convert_ctx {unsigned int downsize_coeff_h; unsigned int downsize_coeff_v; unsigned int num_tiles; size_t* out_tile_map; struct ipu_image_convert_chan* chan; } ;
struct ipu_image_convert_chan {int /*<<< orphan*/  ic_task; struct ipu_image_convert_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int bpp; scalar_t__ planar; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IMAGE_CONVERT_IN ; 
 scalar_t__ IMAGE_CONVERT_OUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ipu_image_convert_ctx*,char*,unsigned int const,unsigned int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int calc_tile_dimensions(struct ipu_image_convert_ctx *ctx,
				struct ipu_image_convert_image *image)
{
	struct ipu_image_convert_chan *chan = ctx->chan;
	struct ipu_image_convert_priv *priv = chan->priv;
	unsigned int max_width = 1024;
	unsigned int max_height = 1024;
	unsigned int i;

	if (image->type == IMAGE_CONVERT_IN) {
		/* Up to 4096x4096 input tile size */
		max_width <<= ctx->downsize_coeff_h;
		max_height <<= ctx->downsize_coeff_v;
	}

	for (i = 0; i < ctx->num_tiles; i++) {
		struct ipu_image_tile *tile;
		const unsigned int row = i / image->num_cols;
		const unsigned int col = i % image->num_cols;

		if (image->type == IMAGE_CONVERT_OUT)
			tile = &image->tile[ctx->out_tile_map[i]];
		else
			tile = &image->tile[i];

		tile->size = ((tile->height * image->fmt->bpp) >> 3) *
			tile->width;

		if (image->fmt->planar) {
			tile->stride = tile->width;
			tile->rot_stride = tile->height;
		} else {
			tile->stride =
				(image->fmt->bpp * tile->width) >> 3;
			tile->rot_stride =
				(image->fmt->bpp * tile->height) >> 3;
		}

		dev_dbg(priv->ipu->dev,
			"task %u: ctx %p: %s@[%u,%u]: %ux%u@%u,%u\n",
			chan->ic_task, ctx,
			image->type == IMAGE_CONVERT_IN ? "Input" : "Output",
			row, col,
			tile->width, tile->height, tile->left, tile->top);

		if (!tile->width || tile->width > max_width ||
		    !tile->height || tile->height > max_height) {
			dev_err(priv->ipu->dev, "invalid %s tile size: %ux%u\n",
				image->type == IMAGE_CONVERT_IN ? "input" :
				"output", tile->width, tile->height);
			return -EINVAL;
		}
	}

	return 0;
}