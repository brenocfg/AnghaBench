#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vimc_deb_device {int /*<<< orphan*/  src_code; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int index; int /*<<< orphan*/  code; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ IS_SRC (int /*<<< orphan*/ ) ; 
 struct vimc_deb_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 TYPE_1__* vimc_deb_pix_map_list ; 

__attribute__((used)) static int vimc_deb_enum_mbus_code(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_mbus_code_enum *code)
{
	/* We only support one format for source pads */
	if (IS_SRC(code->pad)) {
		struct vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

		if (code->index)
			return -EINVAL;

		code->code = vdeb->src_code;
	} else {
		if (code->index >= ARRAY_SIZE(vimc_deb_pix_map_list))
			return -EINVAL;

		code->code = vimc_deb_pix_map_list[code->index].code;
	}

	return 0;
}