#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct rvin_dev {TYPE_2__ source; TYPE_2__ compose; TYPE_2__ crop; TYPE_3__ format; TYPE_1__* parallel; } ;
struct TYPE_5__ {int /*<<< orphan*/  source_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  rvin_format_align (struct rvin_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  vin_to_source (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_reset_format(struct rvin_dev *vin)
{
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = vin->parallel->source_pad,
	};
	int ret;

	ret = v4l2_subdev_call(vin_to_source(vin), pad, get_fmt, NULL, &fmt);
	if (ret)
		return ret;

	v4l2_fill_pix_format(&vin->format, &fmt.format);

	rvin_format_align(vin, &vin->format);

	vin->source.top = 0;
	vin->source.left = 0;
	vin->source.width = vin->format.width;
	vin->source.height = vin->format.height;

	vin->crop = vin->source;
	vin->compose = vin->source;

	return 0;
}