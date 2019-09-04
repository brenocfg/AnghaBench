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
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct csid_device {size_t nformats; TYPE_3__* formats; TYPE_2__* testgen_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {scalar_t__ val; } ;
struct TYPE_5__ {TYPE_1__ cur; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MSM_CSID_PAD_SINK ; 
 struct v4l2_mbus_framefmt* __csid_get_format (struct csid_device*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csid_src_pad_code (struct csid_device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 struct csid_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csid_enum_mbus_code(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code)
{
	struct csid_device *csid = v4l2_get_subdevdata(sd);

	if (code->pad == MSM_CSID_PAD_SINK) {
		if (code->index >= csid->nformats)
			return -EINVAL;

		code->code = csid->formats[code->index].code;
	} else {
		if (csid->testgen_mode->cur.val == 0) {
			struct v4l2_mbus_framefmt *sink_fmt;

			sink_fmt = __csid_get_format(csid, cfg,
						     MSM_CSID_PAD_SINK,
						     code->which);

			code->code = csid_src_pad_code(csid, sink_fmt->code,
						       code->index, 0);
			if (!code->code)
				return -EINVAL;
		} else {
			if (code->index >= csid->nformats)
				return -EINVAL;

			code->code = csid->formats[code->index].code;
		}
	}

	return 0;
}