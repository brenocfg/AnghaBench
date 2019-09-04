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
typedef  scalar_t__ u16 ;
struct ov5640_ctrls {TYPE_2__* exposure; TYPE_1__* auto_exp; } ;
struct ov5640_dev {struct ov5640_ctrls ctrls; } ;
typedef  enum v4l2_exposure_auto_type { ____Placeholder_v4l2_exposure_auto_type } v4l2_exposure_auto_type ;
struct TYPE_4__ {scalar_t__ val; scalar_t__ is_new; } ;
struct TYPE_3__ {scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_AEC_PK_VTS ; 
 int V4L2_EXPOSURE_AUTO ; 
 int ov5640_get_vts (struct ov5640_dev*) ; 
 int ov5640_read_reg16 (struct ov5640_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ov5640_set_autoexposure (struct ov5640_dev*,int) ; 
 int ov5640_set_exposure (struct ov5640_dev*,scalar_t__) ; 

__attribute__((used)) static int ov5640_set_ctrl_exposure(struct ov5640_dev *sensor,
				    enum v4l2_exposure_auto_type auto_exposure)
{
	struct ov5640_ctrls *ctrls = &sensor->ctrls;
	bool auto_exp = (auto_exposure == V4L2_EXPOSURE_AUTO);
	int ret = 0;

	if (ctrls->auto_exp->is_new) {
		ret = ov5640_set_autoexposure(sensor, auto_exp);
		if (ret)
			return ret;
	}

	if (!auto_exp && ctrls->exposure->is_new) {
		u16 max_exp;

		ret = ov5640_read_reg16(sensor, OV5640_REG_AEC_PK_VTS,
					&max_exp);
		if (ret)
			return ret;
		ret = ov5640_get_vts(sensor);
		if (ret < 0)
			return ret;
		max_exp += ret;
		ret = 0;

		if (ctrls->exposure->val < max_exp)
			ret = ov5640_set_exposure(sensor, ctrls->exposure->val);
	}

	return ret;
}