#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {size_t index; int /*<<< orphan*/  code; } ;
struct v4l2_subdev {int dummy; } ;
struct adv76xx_state {TYPE_2__* info; } ;
struct TYPE_4__ {size_t nformats; TYPE_1__* formats; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv76xx_enum_mbus_code(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	struct adv76xx_state *state = to_state(sd);

	if (code->index >= state->info->nformats)
		return -EINVAL;

	code->code = state->info->formats[code->index].code;

	return 0;
}