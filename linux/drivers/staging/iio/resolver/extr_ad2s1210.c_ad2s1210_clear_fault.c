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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad2s1210_state {int /*<<< orphan*/  lock; int /*<<< orphan*/ * gpios; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD2S1210_REG_FAULT ; 
 size_t AD2S1210_SAMPLE ; 
 int ad2s1210_config_read (struct ad2s1210_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad2s1210_state* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static ssize_t ad2s1210_clear_fault(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	int ret;

	mutex_lock(&st->lock);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
	ret = ad2s1210_config_read(st, AD2S1210_REG_FAULT);
	if (ret < 0)
		goto error_ret;
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
error_ret:
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : len;
}