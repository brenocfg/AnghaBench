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
struct v4l2_subdev_mbus_code_enum {size_t index; int /*<<< orphan*/  code; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t N_OV7740_FMTS ; 
 TYPE_1__* ov7740_formats ; 

__attribute__((used)) static int ov7740_enum_mbus_code(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= N_OV7740_FMTS)
		return -EINVAL;

	code->code = ov7740_formats[code->index].mbus_code;

	return 0;
}