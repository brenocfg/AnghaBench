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
struct sca3000_state {int* rx; TYPE_1__* info; } ;
struct TYPE_2__ {int measurement_mode_3db_freq; int option_mode_1_3db_freq; int option_mode_2_3db_freq; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  SCA3000_REG_MODE_ADDR ; 
#define  SCA3000_REG_MODE_MEAS_MODE_MOT_DET 131 
#define  SCA3000_REG_MODE_MEAS_MODE_NORMAL 130 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_1 129 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_2 128 
 int SCA3000_REG_MODE_MODE_MASK ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_read_3db_freq(struct sca3000_state *st, int *val)
{
	int ret;

	ret = sca3000_read_data_short(st, SCA3000_REG_MODE_ADDR, 1);
	if (ret)
		return ret;

	/* mask bottom 2 bits - only ones that are relevant */
	st->rx[0] &= SCA3000_REG_MODE_MODE_MASK;
	switch (st->rx[0]) {
	case SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		*val = st->info->measurement_mode_3db_freq;
		return IIO_VAL_INT;
	case SCA3000_REG_MODE_MEAS_MODE_MOT_DET:
		return -EBUSY;
	case SCA3000_REG_MODE_MEAS_MODE_OP_1:
		*val = st->info->option_mode_1_3db_freq;
		return IIO_VAL_INT;
	case SCA3000_REG_MODE_MEAS_MODE_OP_2:
		*val = st->info->option_mode_2_3db_freq;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}