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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct ispif_line {size_t nformats; int /*<<< orphan*/ * formats; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MSM_ISPIF_PAD_SINK ; 
 struct v4l2_mbus_framefmt* __ispif_get_format (struct ispif_line*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ispif_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ispif_enum_mbus_code(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_mbus_code_enum *code)
{
	struct ispif_line *line = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (code->pad == MSM_ISPIF_PAD_SINK) {
		if (code->index >= line->nformats)
			return -EINVAL;

		code->code = line->formats[code->index];
	} else {
		if (code->index > 0)
			return -EINVAL;

		format = __ispif_get_format(line, cfg, MSM_ISPIF_PAD_SINK,
					    code->which);

		code->code = format->code;
	}

	return 0;
}