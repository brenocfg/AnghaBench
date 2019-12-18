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
typedef  int v4l2_std_id ;
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
struct sh_vou_geometry {unsigned int in_width; unsigned int in_height; int scale_idx_h; int scale_idx_v; TYPE_1__ output; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int UINT_MAX ; 
 int V4L2_STD_525_60 ; 
 unsigned int VOU_MAX_IMAGE_WIDTH ; 
 int /*<<< orphan*/  VOU_MIN_IMAGE_HEIGHT ; 
 int /*<<< orphan*/  VOU_MIN_IMAGE_WIDTH ; 
 unsigned int abs (unsigned int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (unsigned int*,int /*<<< orphan*/ ,unsigned int,int,unsigned int*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int* vou_scale_h_den ; 
 unsigned int* vou_scale_h_num ; 
 unsigned int* vou_scale_v_den ; 
 unsigned int* vou_scale_v_num ; 

__attribute__((used)) static void vou_adjust_input(struct sh_vou_geometry *geo, v4l2_std_id std)
{
	/* The compiler cannot know, that best and idx will indeed be set */
	unsigned int best_err = UINT_MAX, best = 0, img_height_max;
	int i, idx = 0;

	if (std & V4L2_STD_525_60)
		img_height_max = 480;
	else
		img_height_max = 576;

	/* Image width must be a multiple of 4 */
	v4l_bound_align_image(&geo->in_width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &geo->in_height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	/* Select scales to come as close as possible to the output image */
	for (i = ARRAY_SIZE(vou_scale_h_num) - 1; i >= 0; i--) {
		unsigned int err;
		unsigned int found = geo->output.width * vou_scale_h_den[i] /
			vou_scale_h_num[i];

		if (found > VOU_MAX_IMAGE_WIDTH)
			/* scales increase */
			break;

		err = abs(found - geo->in_width);
		if (err < best_err) {
			best_err = err;
			idx = i;
			best = found;
		}
		if (!err)
			break;
	}

	geo->in_width = best;
	geo->scale_idx_h = idx;

	best_err = UINT_MAX;

	/* This loop can be replaced with one division */
	for (i = ARRAY_SIZE(vou_scale_v_num) - 1; i >= 0; i--) {
		unsigned int err;
		unsigned int found = geo->output.height * vou_scale_v_den[i] /
			vou_scale_v_num[i];

		if (found > img_height_max)
			/* scales increase */
			break;

		err = abs(found - geo->in_height);
		if (err < best_err) {
			best_err = err;
			idx = i;
			best = found;
		}
		if (!err)
			break;
	}

	geo->in_height = best;
	geo->scale_idx_v = idx;
}