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
struct ov965x_ctrls {TYPE_2__* gain; TYPE_1__* auto_gain; } ;
struct ov965x {struct ov965x_ctrls ctrls; } ;
struct TYPE_4__ {unsigned int val; scalar_t__ is_new; } ;
struct TYPE_3__ {scalar_t__ val; scalar_t__ is_new; } ;

/* Variables and functions */
 unsigned int COM8_AGC ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int /*<<< orphan*/  REG_GAIN ; 
 int /*<<< orphan*/  REG_VREF ; 
 unsigned int VREF_GAIN_MASK ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,unsigned int*) ; 
 int ov965x_write (struct ov965x*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ov965x_set_gain(struct ov965x *ov965x, int auto_gain)
{
	struct ov965x_ctrls *ctrls = &ov965x->ctrls;
	int ret = 0;
	u8 reg;
	/*
	 * For manual mode we need to disable AGC first, so
	 * gain value in REG_VREF, REG_GAIN is not overwritten.
	 */
	if (ctrls->auto_gain->is_new) {
		ret = ov965x_read(ov965x, REG_COM8, &reg);
		if (ret < 0)
			return ret;
		if (ctrls->auto_gain->val)
			reg |= COM8_AGC;
		else
			reg &= ~COM8_AGC;
		ret = ov965x_write(ov965x, REG_COM8, reg);
		if (ret < 0)
			return ret;
	}

	if (ctrls->gain->is_new && !auto_gain) {
		unsigned int gain = ctrls->gain->val;
		unsigned int rgain;
		int m;
		/*
		 * Convert gain control value to the sensor's gain
		 * registers (VREF[7:6], GAIN[7:0]) format.
		 */
		for (m = 6; m >= 0; m--)
			if (gain >= (1 << m) * 16)
				break;

		/* Sanity check: don't adjust the gain with a negative value */
		if (m < 0)
			return -EINVAL;

		rgain = (gain - ((1 << m) * 16)) / (1 << m);
		rgain |= (((1 << m) - 1) << 4);

		ret = ov965x_write(ov965x, REG_GAIN, rgain & 0xff);
		if (ret < 0)
			return ret;
		ret = ov965x_read(ov965x, REG_VREF, &reg);
		if (ret < 0)
			return ret;
		reg &= ~VREF_GAIN_MASK;
		reg |= (((rgain >> 8) & 0x3) << 6);
		ret = ov965x_write(ov965x, REG_VREF, reg);
		if (ret < 0)
			return ret;
		/* Return updated control's value to userspace */
		ctrls->gain->val = (1 << m) * (16 + (rgain & 0xf));
	}

	return ret;
}