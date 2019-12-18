#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipu_image_tile {unsigned int left; unsigned int width; unsigned int top; unsigned int height; } ;
struct ipu_image_convert_image {unsigned int num_rows; unsigned int num_cols; struct ipu_image_tile* tile; } ;
struct ipu_image_convert_ctx {size_t* out_tile_map; int /*<<< orphan*/  rot_mode; } ;

/* Variables and functions */
 scalar_t__ ipu_rot_mode_is_irt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_tile_column(struct ipu_image_convert_ctx *ctx,
			     unsigned int col,
			     struct ipu_image_convert_image *in,
			     unsigned int in_left, unsigned int in_width,
			     struct ipu_image_convert_image *out,
			     unsigned int out_left, unsigned int out_width)
{
	unsigned int row, tile_idx;
	struct ipu_image_tile *in_tile, *out_tile;

	for (row = 0; row < in->num_rows; row++) {
		tile_idx = in->num_cols * row + col;
		in_tile = &in->tile[tile_idx];
		out_tile = &out->tile[ctx->out_tile_map[tile_idx]];

		in_tile->left = in_left;
		in_tile->width = in_width;

		if (ipu_rot_mode_is_irt(ctx->rot_mode)) {
			out_tile->top = out_left;
			out_tile->height = out_width;
		} else {
			out_tile->left = out_left;
			out_tile->width = out_width;
		}
	}
}