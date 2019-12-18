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
typedef  scalar_t__ u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int index; scalar_t__ code; } ;
struct v4l2_subdev {int dummy; } ;
struct et8ek8_mode {scalar_t__ bus_format; } ;
struct et8ek8_reglist {scalar_t__ type; struct et8ek8_mode mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ET8EK8_REGLIST_MODE ; 
 int MAX_FMTS ; 
 struct et8ek8_reglist** et8ek8_reglist_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meta_reglist ; 

__attribute__((used)) static int et8ek8_enum_mbus_code(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	struct et8ek8_reglist **list =
			et8ek8_reglist_first(&meta_reglist);
	u32 pixelformat[MAX_FMTS];
	int npixelformat = 0;

	if (code->index >= MAX_FMTS)
		return -EINVAL;

	for (; *list; list++) {
		struct et8ek8_mode *mode = &(*list)->mode;
		int i;

		if ((*list)->type != ET8EK8_REGLIST_MODE)
			continue;

		for (i = 0; i < npixelformat; i++) {
			if (pixelformat[i] == mode->bus_format)
				break;
		}
		if (i != npixelformat)
			continue;

		if (code->index == npixelformat) {
			code->code = mode->bus_format;
			return 0;
		}

		pixelformat[npixelformat] = mode->bus_format;
		npixelformat++;
	}

	return -EINVAL;
}