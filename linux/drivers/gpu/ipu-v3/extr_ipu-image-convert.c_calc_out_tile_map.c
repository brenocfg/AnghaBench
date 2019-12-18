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
struct ipu_image_convert_image {unsigned int num_rows; unsigned int num_cols; } ;
struct ipu_image_convert_ctx {int /*<<< orphan*/ * out_tile_map; struct ipu_image_convert_image in; } ;

/* Variables and functions */
 int /*<<< orphan*/  transform_tile_index (struct ipu_image_convert_ctx*,unsigned int,unsigned int) ; 

__attribute__((used)) static void calc_out_tile_map(struct ipu_image_convert_ctx *ctx)
{
	struct ipu_image_convert_image *s_image = &ctx->in;
	unsigned int row, col, tile = 0;

	for (row = 0; row < s_image->num_rows; row++) {
		for (col = 0; col < s_image->num_cols; col++) {
			ctx->out_tile_map[tile] =
				transform_tile_index(ctx, row, col);
			tile++;
		}
	}
}