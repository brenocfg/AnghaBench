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
typedef  unsigned long u8 ;
struct ov965x {TYPE_3__* fiv; TYPE_1__* frame_size; } ;
struct TYPE_5__ {unsigned long denominator; unsigned long numerator; } ;
struct TYPE_6__ {TYPE_2__ interval; } ;
struct TYPE_4__ {unsigned long max_exp_lines; } ;

/* Variables and functions */
 unsigned long COM8_BFILT ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int /*<<< orphan*/  REG_MBD ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_50HZ ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_DISABLED ; 
 scalar_t__ WARN_ON (int) ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,unsigned long*) ; 
 int ov965x_write (struct ov965x*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ov965x_set_banding_filter(struct ov965x *ov965x, int value)
{
	unsigned long mbd, light_freq;
	int ret;
	u8 reg;

	ret = ov965x_read(ov965x, REG_COM8, &reg);
	if (!ret) {
		if (value == V4L2_CID_POWER_LINE_FREQUENCY_DISABLED)
			reg &= ~COM8_BFILT;
		else
			reg |= COM8_BFILT;
		ret = ov965x_write(ov965x, REG_COM8, reg);
	}
	if (value == V4L2_CID_POWER_LINE_FREQUENCY_DISABLED)
		return 0;
	if (WARN_ON(!ov965x->fiv))
		return -EINVAL;
	/* Set minimal exposure time for 50/60 HZ lighting */
	if (value == V4L2_CID_POWER_LINE_FREQUENCY_50HZ)
		light_freq = 50;
	else
		light_freq = 60;
	mbd = (1000UL * ov965x->fiv->interval.denominator *
	       ov965x->frame_size->max_exp_lines) /
	       ov965x->fiv->interval.numerator;
	mbd = ((mbd / (light_freq * 2)) + 500) / 1000UL;

	return ov965x_write(ov965x, REG_MBD, mbd);
}