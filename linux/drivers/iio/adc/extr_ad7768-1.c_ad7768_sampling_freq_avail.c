#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7768_state {int /*<<< orphan*/  mclk_freq; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  clk_div; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_1__* ad7768_clk_config ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,unsigned int) ; 

__attribute__((used)) static ssize_t ad7768_sampling_freq_avail(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7768_state *st = iio_priv(indio_dev);
	unsigned int freq;
	int i, len = 0;

	for (i = 0; i < ARRAY_SIZE(ad7768_clk_config); i++) {
		freq = DIV_ROUND_CLOSEST(st->mclk_freq,
					 ad7768_clk_config[i].clk_div);
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ", freq);
	}

	buf[len - 1] = '\n';

	return len;
}