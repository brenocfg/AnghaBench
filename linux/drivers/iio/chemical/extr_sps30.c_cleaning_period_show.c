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
typedef  int /*<<< orphan*/  u8 ;
struct sps30_state {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPS30_READ_AUTO_CLEANING_PERIOD ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 struct sps30_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int sps30_do_cmd (struct sps30_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t cleaning_period_show(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct sps30_state *state = iio_priv(indio_dev);
	u8 tmp[4];
	int ret;

	mutex_lock(&state->lock);
	ret = sps30_do_cmd(state, SPS30_READ_AUTO_CLEANING_PERIOD, tmp, 4);
	mutex_unlock(&state->lock);
	if (ret)
		return ret;

	return sprintf(buf, "%d\n", get_unaligned_be32(tmp));
}