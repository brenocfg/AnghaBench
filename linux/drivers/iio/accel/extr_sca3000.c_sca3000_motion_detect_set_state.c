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
struct sca3000_state {int* rx; scalar_t__ mo_det_use_count; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_CTRL_SEL_MD_CTRL ; 
 int /*<<< orphan*/  SCA3000_REG_MODE_ADDR ; 
 int SCA3000_REG_MODE_MEAS_MODE_MOT_DET ; 
 int SCA3000_REG_MODE_MODE_MASK ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int** sca3000_addresses ; 
 int sca3000_read_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_motion_detect_set_state(struct iio_dev *indio_dev, int axis,
					   int state)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret, ctrlval;

	/*
	 * First read the motion detector config to find out if
	 * this axis is on
	 */
	ret = sca3000_read_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL);
	if (ret < 0)
		return ret;
	ctrlval = ret;
	/* if off and should be on */
	if (state && !(ctrlval & sca3000_addresses[axis][2])) {
		ret = sca3000_write_ctrl_reg(st,
					     SCA3000_REG_CTRL_SEL_MD_CTRL,
					     ctrlval |
					     sca3000_addresses[axis][2]);
		if (ret)
			return ret;
		st->mo_det_use_count++;
	} else if (!state && (ctrlval & sca3000_addresses[axis][2])) {
		ret = sca3000_write_ctrl_reg(st,
					     SCA3000_REG_CTRL_SEL_MD_CTRL,
					     ctrlval &
					     ~(sca3000_addresses[axis][2]));
		if (ret)
			return ret;
		st->mo_det_use_count--;
	}

	/* read current value of mode register */
	ret = sca3000_read_data_short(st, SCA3000_REG_MODE_ADDR, 1);
	if (ret)
		return ret;
	/* if off and should be on */
	if ((st->mo_det_use_count) &&
	    ((st->rx[0] & SCA3000_REG_MODE_MODE_MASK)
	     != SCA3000_REG_MODE_MEAS_MODE_MOT_DET))
		return sca3000_write_reg(st, SCA3000_REG_MODE_ADDR,
			(st->rx[0] & ~SCA3000_REG_MODE_MODE_MASK)
			| SCA3000_REG_MODE_MEAS_MODE_MOT_DET);
	/* if on and should be off */
	else if (!(st->mo_det_use_count) &&
		 ((st->rx[0] & SCA3000_REG_MODE_MODE_MASK)
		  == SCA3000_REG_MODE_MEAS_MODE_MOT_DET))
		return sca3000_write_reg(st, SCA3000_REG_MODE_ADDR,
			st->rx[0] & SCA3000_REG_MODE_MODE_MASK);
	else
		return 0;
}