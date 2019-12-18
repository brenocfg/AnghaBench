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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
typedef  enum hpd_mode { ____Placeholder_hpd_mode } hpd_mode ;

/* Variables and functions */
 int HPD_AUTO_HP_OTHER ; 
#define  HPD_HIGH_BP 132 
#define  HPD_HIGH_OTHER 131 
#define  HPD_LOW_BP 130 
#define  HPD_LOW_OTHER 129 
 int HPD_MAN_CTRL_5VEN ; 
 int HPD_MAN_CTRL_HPD_A ; 
 int HPD_MAN_CTRL_HPD_B ; 
 int HPD_MAN_CTRL_HPD_PULSE ; 
 int HPD_POWER_BP_MASK ; 
 int HPD_POWER_BP_SHIFT ; 
#define  HPD_PULSE 128 
 int /*<<< orphan*/  REG_HPD_AUTO_CTRL ; 
 int /*<<< orphan*/  REG_HPD_MAN_CTRL ; 
 int /*<<< orphan*/  REG_HPD_POWER ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda1997x_manual_hpd(struct v4l2_subdev *sd, enum hpd_mode mode)
{
	u8 hpd_auto, hpd_pwr, hpd_man;

	hpd_auto = io_read(sd, REG_HPD_AUTO_CTRL);
	hpd_pwr = io_read(sd, REG_HPD_POWER);
	hpd_man = io_read(sd, REG_HPD_MAN_CTRL);

	/* mask out unused bits */
	hpd_man &= (HPD_MAN_CTRL_HPD_PULSE |
		    HPD_MAN_CTRL_5VEN |
		    HPD_MAN_CTRL_HPD_B |
		    HPD_MAN_CTRL_HPD_A);

	switch (mode) {
	/* HPD low and pulse of at least 100ms */
	case HPD_LOW_BP:
		/* hpd_bp=0 */
		hpd_pwr &= ~HPD_POWER_BP_MASK;
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		io_write(sd, REG_HPD_POWER, hpd_pwr);
		io_write(sd, REG_HPD_MAN_CTRL, hpd_man);
		break;
	/* HPD high */
	case HPD_HIGH_BP:
		/* hpd_bp=1 */
		hpd_pwr &= ~HPD_POWER_BP_MASK;
		hpd_pwr |= 1 << HPD_POWER_BP_SHIFT;
		io_write(sd, REG_HPD_POWER, hpd_pwr);
		break;
	/* HPD low and pulse of at least 100ms */
	case HPD_LOW_OTHER:
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		/* hp_other=0 */
		hpd_auto &= ~HPD_AUTO_HP_OTHER;
		io_write(sd, REG_HPD_AUTO_CTRL, hpd_auto);
		io_write(sd, REG_HPD_MAN_CTRL, hpd_man);
		break;
	/* HPD high */
	case HPD_HIGH_OTHER:
		hpd_auto |= HPD_AUTO_HP_OTHER;
		io_write(sd, REG_HPD_AUTO_CTRL, hpd_auto);
		break;
	/* HPD low pulse */
	case HPD_PULSE:
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		io_write(sd, REG_HPD_MAN_CTRL, hpd_man);
		break;
	}

	return 0;
}