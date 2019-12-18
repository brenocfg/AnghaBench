#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {TYPE_2__* exposure; TYPE_1__* gain; } ;
struct ov965x {unsigned int exp_row_interval; TYPE_3__ ctrls; int /*<<< orphan*/  power; } ;
struct TYPE_5__ {unsigned int val; } ;
struct TYPE_4__ {unsigned int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AECH ; 
 int /*<<< orphan*/  REG_AECHM ; 
 int /*<<< orphan*/  REG_COM1 ; 
 int /*<<< orphan*/  REG_GAIN ; 
 int /*<<< orphan*/  REG_VREF ; 
#define  V4L2_CID_AUTOGAIN 129 
#define  V4L2_CID_EXPOSURE_AUTO 128 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int fls (unsigned int) ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int __g_volatile_ctrl(struct ov965x *ov965x, struct v4l2_ctrl *ctrl)
{
	unsigned int exposure, gain, m;
	u8 reg0, reg1, reg2;
	int ret;

	if (!ov965x->power)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		if (!ctrl->val)
			return 0;
		ret = ov965x_read(ov965x, REG_GAIN, &reg0);
		if (ret < 0)
			return ret;
		ret = ov965x_read(ov965x, REG_VREF, &reg1);
		if (ret < 0)
			return ret;
		gain = ((reg1 >> 6) << 8) | reg0;
		m = 0x01 << fls(gain >> 4);
		ov965x->ctrls.gain->val = m * (16 + (gain & 0xf));
		break;

	case V4L2_CID_EXPOSURE_AUTO:
		if (ctrl->val == V4L2_EXPOSURE_MANUAL)
			return 0;
		ret = ov965x_read(ov965x, REG_COM1, &reg0);
		if (ret < 0)
			return ret;
		ret = ov965x_read(ov965x, REG_AECH, &reg1);
		if (ret < 0)
			return ret;
		ret = ov965x_read(ov965x, REG_AECHM, &reg2);
		if (ret < 0)
			return ret;
		exposure = ((reg2 & 0x3f) << 10) | (reg1 << 2) |
						(reg0 & 0x3);
		ov965x->ctrls.exposure->val = ((exposure *
				ov965x->exp_row_interval) + 50) / 100;
		break;
	}

	return 0;
}