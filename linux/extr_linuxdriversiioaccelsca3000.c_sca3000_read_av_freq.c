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
struct sca3000_state {int* rx; TYPE_1__* info; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int measurement_mode_freq; int option_mode_1_freq; int option_mode_2_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_MODE_ADDR ; 
#define  SCA3000_REG_MODE_MEAS_MODE_NORMAL 130 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_1 129 
#define  SCA3000_REG_MODE_MEAS_MODE_OP_2 128 
 int SCA3000_REG_MODE_MODE_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t sca3000_read_av_freq(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
	int len = 0, ret, val;

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_MODE_ADDR, 1);
	val = st->rx[0];
	mutex_unlock(&st->lock);
	if (ret)
		goto error_ret;

	switch (val & SCA3000_REG_MODE_MODE_MASK) {
	case SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		len += sprintf(buf + len, "%d %d %d\n",
			       st->info->measurement_mode_freq,
			       st->info->measurement_mode_freq / 2,
			       st->info->measurement_mode_freq / 4);
		break;
	case SCA3000_REG_MODE_MEAS_MODE_OP_1:
		len += sprintf(buf + len, "%d %d %d\n",
			       st->info->option_mode_1_freq,
			       st->info->option_mode_1_freq / 2,
			       st->info->option_mode_1_freq / 4);
		break;
	case SCA3000_REG_MODE_MEAS_MODE_OP_2:
		len += sprintf(buf + len, "%d %d %d\n",
			       st->info->option_mode_2_freq,
			       st->info->option_mode_2_freq / 2,
			       st->info->option_mode_2_freq / 4);
		break;
	}
	return len;
error_ret:
	return ret;
}