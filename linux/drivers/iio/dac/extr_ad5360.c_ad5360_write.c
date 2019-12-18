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
struct iio_dev {int /*<<< orphan*/  mlock; } ;

/* Variables and functions */
 int ad5360_write_unlocked (struct iio_dev*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5360_write(struct iio_dev *indio_dev, unsigned int cmd,
	unsigned int addr, unsigned int val, unsigned int shift)
{
	int ret;

	mutex_lock(&indio_dev->mlock);
	ret = ad5360_write_unlocked(indio_dev, cmd, addr, val, shift);
	mutex_unlock(&indio_dev->mlock);

	return ret;
}