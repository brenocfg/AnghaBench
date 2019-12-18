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
struct v4l2_subdev {int dummy; } ;
struct ov7670_info {scalar_t__ pll_bypass; int /*<<< orphan*/  clkrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBLV_BYPASS ; 
 int /*<<< orphan*/  DBLV_X4 ; 
 int /*<<< orphan*/  REG_CLKRC ; 
 int /*<<< orphan*/  REG_DBLV ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7675_apply_framerate(struct v4l2_subdev *sd)
{
	struct ov7670_info *info = to_state(sd);
	int ret;

	ret = ov7670_write(sd, REG_CLKRC, info->clkrc);
	if (ret < 0)
		return ret;

	return ov7670_write(sd, REG_DBLV,
			    info->pll_bypass ? DBLV_BYPASS : DBLV_X4);
}