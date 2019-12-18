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
struct ipu_image_convert_image {TYPE_1__* fmt; } ;
struct ipu_image_convert_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ planar; } ;

/* Variables and functions */
 int calc_tile_offsets_packed (struct ipu_image_convert_ctx*,struct ipu_image_convert_image*) ; 
 int calc_tile_offsets_planar (struct ipu_image_convert_ctx*,struct ipu_image_convert_image*) ; 

__attribute__((used)) static int calc_tile_offsets(struct ipu_image_convert_ctx *ctx,
			      struct ipu_image_convert_image *image)
{
	if (image->fmt->planar)
		return calc_tile_offsets_planar(ctx, image);

	return calc_tile_offsets_packed(ctx, image);
}