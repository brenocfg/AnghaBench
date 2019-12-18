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
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad2s1210_state {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ad2s1210_config_read (struct ad2s1210_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ad2s1210_state* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad2s1210_show_reg(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	struct iio_dev_attr *iattr = to_iio_dev_attr(attr);
	int ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_read(st, iattr->address);
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : sprintf(buf, "%d\n", ret);
}