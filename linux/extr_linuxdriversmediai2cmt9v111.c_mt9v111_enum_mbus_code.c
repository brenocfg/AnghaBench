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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int index; int /*<<< orphan*/  code; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* mt9v111_formats ; 

__attribute__((used)) static int mt9v111_enum_mbus_code(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index > ARRAY_SIZE(mt9v111_formats) - 1)
		return -EINVAL;

	code->code = mt9v111_formats[code->index].code;

	return 0;
}