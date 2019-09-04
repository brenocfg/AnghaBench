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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct saa6752hs_state {size_t video_format; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 size_t SAA6752HS_VF_D1 ; 
 size_t SAA6752HS_VF_UNKNOWN ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 struct saa6752hs_state* to_state (struct v4l2_subdev*) ; 
 TYPE_3__* v4l2_format_table ; 

__attribute__((used)) static int saa6752hs_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *f = &format->format;
	struct saa6752hs_state *h = to_state(sd);

	if (format->pad)
		return -EINVAL;

	if (h->video_format == SAA6752HS_VF_UNKNOWN)
		h->video_format = SAA6752HS_VF_D1;
	f->width = v4l2_format_table[h->video_format].fmt.pix.width;
	f->height = v4l2_format_table[h->video_format].fmt.pix.height;
	f->code = MEDIA_BUS_FMT_FIXED;
	f->field = V4L2_FIELD_INTERLACED;
	f->colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}