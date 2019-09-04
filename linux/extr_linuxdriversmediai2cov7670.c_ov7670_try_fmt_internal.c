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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct ov7670_win_size {scalar_t__ width; scalar_t__ height; } ;
struct ov7670_info {scalar_t__ min_width; scalar_t__ min_height; struct v4l2_mbus_framefmt format; TYPE_1__* devtype; } ;
struct ov7670_format_struct {scalar_t__ mbus_code; int /*<<< orphan*/  colorspace; } ;
struct TYPE_2__ {unsigned int n_win_sizes; struct ov7670_win_size* win_sizes; } ;

/* Variables and functions */
 int N_OV7670_FMTS ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct ov7670_format_struct* ov7670_formats ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_try_fmt_internal(struct v4l2_subdev *sd,
		struct v4l2_mbus_framefmt *fmt,
		struct ov7670_format_struct **ret_fmt,
		struct ov7670_win_size **ret_wsize)
{
	int index, i;
	struct ov7670_win_size *wsize;
	struct ov7670_info *info = to_state(sd);
	unsigned int n_win_sizes = info->devtype->n_win_sizes;
	unsigned int win_sizes_limit = n_win_sizes;

	for (index = 0; index < N_OV7670_FMTS; index++)
		if (ov7670_formats[index].mbus_code == fmt->code)
			break;
	if (index >= N_OV7670_FMTS) {
		/* default to first format */
		index = 0;
		fmt->code = ov7670_formats[0].mbus_code;
	}
	if (ret_fmt != NULL)
		*ret_fmt = ov7670_formats + index;
	/*
	 * Fields: the OV devices claim to be progressive.
	 */
	fmt->field = V4L2_FIELD_NONE;

	/*
	 * Don't consider values that don't match min_height and min_width
	 * constraints.
	 */
	if (info->min_width || info->min_height)
		for (i = 0; i < n_win_sizes; i++) {
			wsize = info->devtype->win_sizes + i;

			if (wsize->width < info->min_width ||
				wsize->height < info->min_height) {
				win_sizes_limit = i;
				break;
			}
		}
	/*
	 * Round requested image size down to the nearest
	 * we support, but not below the smallest.
	 */
	for (wsize = info->devtype->win_sizes;
	     wsize < info->devtype->win_sizes + win_sizes_limit; wsize++)
		if (fmt->width >= wsize->width && fmt->height >= wsize->height)
			break;
	if (wsize >= info->devtype->win_sizes + win_sizes_limit)
		wsize--;   /* Take the smallest one */
	if (ret_wsize != NULL)
		*ret_wsize = wsize;
	/*
	 * Note the size we'll actually handle.
	 */
	fmt->width = wsize->width;
	fmt->height = wsize->height;
	fmt->colorspace = ov7670_formats[index].colorspace;

	info->format = *fmt;

	return 0;
}