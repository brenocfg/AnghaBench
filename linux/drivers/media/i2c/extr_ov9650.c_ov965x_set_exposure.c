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
typedef  unsigned int u8 ;
struct ov965x_ctrls {int /*<<< orphan*/  brightness; TYPE_2__* exposure; TYPE_1__* auto_exp; } ;
struct ov965x {int exp_row_interval; struct ov965x_ctrls ctrls; } ;
struct TYPE_4__ {int val; scalar_t__ is_new; } ;
struct TYPE_3__ {scalar_t__ is_new; } ;

/* Variables and functions */
 unsigned int COM8_AEC ; 
 unsigned int COM8_AGC ; 
 int /*<<< orphan*/  REG_AECH ; 
 int /*<<< orphan*/  REG_AECHM ; 
 int /*<<< orphan*/  REG_COM1 ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int V4L2_EXPOSURE_AUTO ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,unsigned int*) ; 
 int ov965x_write (struct ov965x*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  v4l2_ctrl_activate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov965x_set_exposure(struct ov965x *ov965x, int exp)
{
	struct ov965x_ctrls *ctrls = &ov965x->ctrls;
	bool auto_exposure = (exp == V4L2_EXPOSURE_AUTO);
	int ret;
	u8 reg;

	if (ctrls->auto_exp->is_new) {
		ret = ov965x_read(ov965x, REG_COM8, &reg);
		if (ret < 0)
			return ret;
		if (auto_exposure)
			reg |= (COM8_AEC | COM8_AGC);
		else
			reg &= ~(COM8_AEC | COM8_AGC);
		ret = ov965x_write(ov965x, REG_COM8, reg);
		if (ret < 0)
			return ret;
	}

	if (!auto_exposure && ctrls->exposure->is_new) {
		unsigned int exposure = (ctrls->exposure->val * 100)
					 / ov965x->exp_row_interval;
		/*
		 * Manual exposure value
		 * [b15:b0] - AECHM (b15:b10), AECH (b9:b2), COM1 (b1:b0)
		 */
		ret = ov965x_write(ov965x, REG_COM1, exposure & 0x3);
		if (!ret)
			ret = ov965x_write(ov965x, REG_AECH,
					   (exposure >> 2) & 0xff);
		if (!ret)
			ret = ov965x_write(ov965x, REG_AECHM,
					   (exposure >> 10) & 0x3f);
		/* Update the value to minimize rounding errors */
		ctrls->exposure->val = ((exposure * ov965x->exp_row_interval)
							+ 50) / 100;
		if (ret < 0)
			return ret;
	}

	v4l2_ctrl_activate(ov965x->ctrls.brightness, !exp);
	return 0;
}