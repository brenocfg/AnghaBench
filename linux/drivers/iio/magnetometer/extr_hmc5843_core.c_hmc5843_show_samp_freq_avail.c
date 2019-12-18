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
struct hmc5843_data {TYPE_1__* variant; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int n_regval_to_samp_freq; int /*<<< orphan*/ ** regval_to_samp_freq; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct hmc5843_data* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ssize_t hmc5843_show_samp_freq_avail(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct hmc5843_data *data = iio_priv(dev_to_iio_dev(dev));
	size_t len = 0;
	int i;

	for (i = 0; i < data->variant->n_regval_to_samp_freq; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len,
			"%d.%d ", data->variant->regval_to_samp_freq[i][0],
			data->variant->regval_to_samp_freq[i][1]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	return len;
}