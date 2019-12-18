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
struct as3935_state {int /*<<< orphan*/  lock; scalar_t__ noise_tripped; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct as3935_state* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ssize_t as3935_noise_level_tripped_show(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct as3935_state *st = iio_priv(dev_to_iio_dev(dev));
	int ret;

	mutex_lock(&st->lock);
	ret = sprintf(buf, "%d\n", !time_after(jiffies, st->noise_tripped + HZ));
	mutex_unlock(&st->lock);

	return ret;
}