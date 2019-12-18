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
struct TYPE_2__ {int x; int y; int width; int height; } ;
struct scaler_data {scalar_t__ format; TYPE_1__ viewport; } ;
struct rect {int x; int y; int width; int height; } ;

/* Variables and functions */
 scalar_t__ PIXEL_FORMAT_420BPP8 ; 

__attribute__((used)) static void calculate_viewport(
		const struct scaler_data *scl_data,
		struct rect *luma_viewport,
		struct rect *chroma_viewport)
{
	/*Do not set chroma vp for rgb444 pixel format*/
	luma_viewport->x = scl_data->viewport.x - scl_data->viewport.x % 2;
	luma_viewport->y = scl_data->viewport.y - scl_data->viewport.y % 2;
	luma_viewport->width =
		scl_data->viewport.width - scl_data->viewport.width % 2;
	luma_viewport->height =
		scl_data->viewport.height - scl_data->viewport.height % 2;
	chroma_viewport->x = luma_viewport->x;
	chroma_viewport->y = luma_viewport->y;
	chroma_viewport->height = luma_viewport->height;
	chroma_viewport->width = luma_viewport->width;

	if (scl_data->format == PIXEL_FORMAT_420BPP8) {
		luma_viewport->height += luma_viewport->height % 2;
		luma_viewport->width += luma_viewport->width % 2;
		/*for 420 video chroma is 1/4 the area of luma, scaled
		 *vertically and horizontally
		 */
		chroma_viewport->x = luma_viewport->x / 2;
		chroma_viewport->y = luma_viewport->y / 2;
		chroma_viewport->height = luma_viewport->height / 2;
		chroma_viewport->width = luma_viewport->width / 2;
	}
}