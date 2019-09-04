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
struct v4l2_subdev_mbus_code_enum {int /*<<< orphan*/  code; scalar_t__ index; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct mt9p031 {TYPE_1__ format; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mt9p031* to_mt9p031 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9p031_enum_mbus_code(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);

	if (code->pad || code->index)
		return -EINVAL;

	code->code = mt9p031->format.code;
	return 0;
}