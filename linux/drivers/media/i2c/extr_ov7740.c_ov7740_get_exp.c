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
struct v4l2_ctrl {scalar_t__ val; } ;
struct regmap {int dummy; } ;
struct ov7740 {TYPE_1__* exposure; struct regmap* regmap; } ;
struct TYPE_2__ {unsigned int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AEC ; 
 int /*<<< orphan*/  REG_HAEC ; 
 scalar_t__ V4L2_EXPOSURE_MANUAL ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ov7740_get_exp(struct ov7740 *ov7740, struct v4l2_ctrl *ctrl)
{
	struct regmap *regmap = ov7740->regmap;
	unsigned int value0, value1;
	int ret;

	if (ctrl->val == V4L2_EXPOSURE_MANUAL)
		return 0;

	ret = regmap_read(regmap, REG_AEC, &value0);
	if (ret)
		return ret;
	ret = regmap_read(regmap, REG_HAEC, &value1);
	if (ret)
		return ret;

	ov7740->exposure->val = (value1 << 8) | (value0 & 0xff);

	return 0;
}