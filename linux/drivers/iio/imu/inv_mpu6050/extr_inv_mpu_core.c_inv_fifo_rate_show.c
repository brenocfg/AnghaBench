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
struct TYPE_2__ {int /*<<< orphan*/  divider; } ;
struct inv_mpu6050_state {int /*<<< orphan*/  lock; TYPE_1__ chip_config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned int INV_MPU6050_DIVIDER_TO_FIFO_RATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct inv_mpu6050_state* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t
inv_fifo_rate_show(struct device *dev, struct device_attribute *attr,
		   char *buf)
{
	struct inv_mpu6050_state *st = iio_priv(dev_to_iio_dev(dev));
	unsigned fifo_rate;

	mutex_lock(&st->lock);
	fifo_rate = INV_MPU6050_DIVIDER_TO_FIFO_RATE(st->chip_config.divider);
	mutex_unlock(&st->lock);

	return scnprintf(buf, PAGE_SIZE, "%u\n", fifo_rate);
}