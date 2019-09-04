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
struct sca3000_state {int* rx; } ;
struct sca3000_chip_info {int measurement_mode_freq; int option_mode_1_freq; int option_mode_2_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCA3000_REG_MODE_ADDR ; 
#define  SCA3000_REG_MODE_MEAS_MODE_NORMAL 130 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_1 129 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_2 128 
 int SCA3000_REG_MODE_MODE_MASK ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int __sca3000_get_base_freq(struct sca3000_state *st,
					  const struct sca3000_chip_info *info,
					  int *base_freq)
{
	int ret;

	ret = sca3000_read_data_short(st, SCA3000_REG_MODE_ADDR, 1);
	if (ret)
		goto error_ret;
	switch (SCA3000_REG_MODE_MODE_MASK & st->rx[0]) {
	case SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		*base_freq = info->measurement_mode_freq;
		break;
	case SCA3000_REG_MODE_MEAS_MODE_OP_1:
		*base_freq = info->option_mode_1_freq;
		break;
	case SCA3000_REG_MODE_MEAS_MODE_OP_2:
		*base_freq = info->option_mode_2_freq;
		break;
	default:
		ret = -EINVAL;
	}
error_ret:
	return ret;
}