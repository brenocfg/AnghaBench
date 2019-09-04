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
typedef  int /*<<< orphan*/  u32 ;
struct ipu_image_pixfmt {int bpp; } ;
struct TYPE_2__ {void* pixelformat; int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  field; } ;
struct ipu_image {TYPE_1__ pix; } ;
typedef  enum ipu_rotate_mode { ____Placeholder_ipu_rotate_mode } ipu_rotate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_CONVERT_IN ; 
 int /*<<< orphan*/  IMAGE_CONVERT_OUT ; 
 int /*<<< orphan*/  MAX_H ; 
 int /*<<< orphan*/  MAX_W ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 void* V4L2_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  __u32 ; 
 void* clamp_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipu_image_pixfmt* get_format (void*) ; 
 int /*<<< orphan*/  ilog2 (unsigned int) ; 
 scalar_t__ ipu_rot_mode_is_irt (int) ; 
 void* max_t (int /*<<< orphan*/ ,int,int) ; 
 unsigned int num_stripes (int) ; 
 unsigned int tile_height_align (int /*<<< orphan*/ ,int) ; 
 unsigned int tile_width_align (struct ipu_image_pixfmt const*) ; 

void ipu_image_convert_adjust(struct ipu_image *in, struct ipu_image *out,
			      enum ipu_rotate_mode rot_mode)
{
	const struct ipu_image_pixfmt *infmt, *outfmt;
	unsigned int num_in_rows, num_in_cols;
	unsigned int num_out_rows, num_out_cols;
	u32 w_align, h_align;

	infmt = get_format(in->pix.pixelformat);
	outfmt = get_format(out->pix.pixelformat);

	/* set some default pixel formats if needed */
	if (!infmt) {
		in->pix.pixelformat = V4L2_PIX_FMT_RGB24;
		infmt = get_format(V4L2_PIX_FMT_RGB24);
	}
	if (!outfmt) {
		out->pix.pixelformat = V4L2_PIX_FMT_RGB24;
		outfmt = get_format(V4L2_PIX_FMT_RGB24);
	}

	/* image converter does not handle fields */
	in->pix.field = out->pix.field = V4L2_FIELD_NONE;

	/* resizer cannot downsize more than 4:1 */
	if (ipu_rot_mode_is_irt(rot_mode)) {
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.width / 4);
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.height / 4);
	} else {
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.width / 4);
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.height / 4);
	}

	/* get tiling rows/cols from output format */
	num_out_rows = num_stripes(out->pix.height);
	num_out_cols = num_stripes(out->pix.width);
	if (ipu_rot_mode_is_irt(rot_mode)) {
		num_in_rows = num_out_cols;
		num_in_cols = num_out_rows;
	} else {
		num_in_rows = num_out_rows;
		num_in_cols = num_out_cols;
	}

	/* align input width/height */
	w_align = ilog2(tile_width_align(infmt) * num_in_cols);
	h_align = ilog2(tile_height_align(IMAGE_CONVERT_IN, rot_mode) *
			num_in_rows);
	in->pix.width = clamp_align(in->pix.width, MIN_W, MAX_W, w_align);
	in->pix.height = clamp_align(in->pix.height, MIN_H, MAX_H, h_align);

	/* align output width/height */
	w_align = ilog2(tile_width_align(outfmt) * num_out_cols);
	h_align = ilog2(tile_height_align(IMAGE_CONVERT_OUT, rot_mode) *
			num_out_rows);
	out->pix.width = clamp_align(out->pix.width, MIN_W, MAX_W, w_align);
	out->pix.height = clamp_align(out->pix.height, MIN_H, MAX_H, h_align);

	/* set input/output strides and image sizes */
	in->pix.bytesperline = (in->pix.width * infmt->bpp) >> 3;
	in->pix.sizeimage = in->pix.height * in->pix.bytesperline;
	out->pix.bytesperline = (out->pix.width * outfmt->bpp) >> 3;
	out->pix.sizeimage = out->pix.height * out->pix.bytesperline;
}