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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct envelope {unsigned long comp_interval; int /*<<< orphan*/  read_lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct envelope* iio_priv (struct iio_dev*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t envelope_store_comp_interval(struct iio_dev *indio_dev,
					    uintptr_t private,
					    struct iio_chan_spec const *ch,
					    const char *buf, size_t len)
{
	struct envelope *env = iio_priv(indio_dev);
	unsigned long interval;
	int ret;

	ret = kstrtoul(buf, 0, &interval);
	if (ret < 0)
		return ret;
	if (interval > 1000)
		return -EINVAL;

	mutex_lock(&env->read_lock);
	env->comp_interval = interval;
	mutex_unlock(&env->read_lock);

	return len;
}