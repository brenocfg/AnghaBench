#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipu_image_tile {int height; int width; int size; int stride; int rot_stride; } ;
struct TYPE_4__ {int height; int width; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct ipu_image_convert_image {int num_rows; int num_cols; TYPE_3__* fmt; TYPE_2__ base; struct ipu_image_tile* tile; } ;
struct ipu_image_convert_ctx {int num_tiles; } ;
struct TYPE_6__ {int bpp; scalar_t__ planar; } ;

/* Variables and functions */

__attribute__((used)) static void calc_tile_dimensions(struct ipu_image_convert_ctx *ctx,
				 struct ipu_image_convert_image *image)
{
	int i;

	for (i = 0; i < ctx->num_tiles; i++) {
		struct ipu_image_tile *tile = &image->tile[i];

		tile->height = image->base.pix.height / image->num_rows;
		tile->width = image->base.pix.width / image->num_cols;
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
	}
}