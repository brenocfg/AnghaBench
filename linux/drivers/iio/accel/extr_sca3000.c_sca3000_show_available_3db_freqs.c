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
struct sca3000_state {TYPE_1__* info; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int measurement_mode_3db_freq; int option_mode_1_3db_freq; int option_mode_2_3db_freq; scalar_t__ option_mode_2; scalar_t__ option_mode_1; } ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
sca3000_show_available_3db_freqs(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
	int len;

	len = sprintf(buf, "%d", st->info->measurement_mode_3db_freq);
	if (st->info->option_mode_1)
		len += sprintf(buf + len, " %d",
			       st->info->option_mode_1_3db_freq);
	if (st->info->option_mode_2)
		len += sprintf(buf + len, " %d",
			       st->info->option_mode_2_3db_freq);
	len += sprintf(buf + len, "\n");

	return len;
}