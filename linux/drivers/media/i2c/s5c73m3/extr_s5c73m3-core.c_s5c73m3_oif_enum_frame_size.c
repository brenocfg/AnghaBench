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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ pad; size_t index; int code; unsigned int max_width; unsigned int min_width; unsigned int max_height; unsigned int min_height; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; } ;
struct s5c73m3_frame_size {unsigned int width; unsigned int height; } ;
struct s5c73m3 {struct s5c73m3_frame_size** oif_pix_size; } ;
struct TYPE_2__ {unsigned int width; unsigned int height; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OIF_ISP_PAD ; 
 scalar_t__ OIF_JPEG_PAD ; 
 scalar_t__ OIF_SOURCE_PAD ; 
 size_t RES_ISP ; 
 int RES_JPEG ; 
#define  S5C73M3_ISP_FMT 129 
#define  S5C73M3_JPEG_FMT 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int s5c73m3_oif_get_pad_code (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__** s5c73m3_resolutions ; 
 size_t* s5c73m3_resolutions_len ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_oif_enum_frame_size(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int idx;

	if (fse->pad == OIF_SOURCE_PAD) {
		if (fse->index > 0)
			return -EINVAL;

		switch (fse->code) {
		case S5C73M3_JPEG_FMT:
		case S5C73M3_ISP_FMT: {
			unsigned w, h;

			if (fse->which == V4L2_SUBDEV_FORMAT_TRY) {
				struct v4l2_mbus_framefmt *mf;

				mf = v4l2_subdev_get_try_format(sd, cfg,
								OIF_ISP_PAD);

				w = mf->width;
				h = mf->height;
			} else {
				const struct s5c73m3_frame_size *fs;

				fs = state->oif_pix_size[RES_ISP];
				w = fs->width;
				h = fs->height;
			}
			fse->max_width = fse->min_width = w;
			fse->max_height = fse->min_height = h;
			return 0;
		}
		default:
			return -EINVAL;
		}
	}

	if (fse->code != s5c73m3_oif_get_pad_code(fse->pad, 0))
		return -EINVAL;

	if (fse->pad == OIF_JPEG_PAD)
		idx = RES_JPEG;
	else
		idx = RES_ISP;

	if (fse->index >= s5c73m3_resolutions_len[idx])
		return -EINVAL;

	fse->min_width  = s5c73m3_resolutions[idx][fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = s5c73m3_resolutions[idx][fse->index].height;
	fse->min_height = fse->max_height;

	return 0;
}