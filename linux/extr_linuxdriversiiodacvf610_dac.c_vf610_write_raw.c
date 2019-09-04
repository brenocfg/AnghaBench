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
struct vf610_dac {int /*<<< orphan*/  regs; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  VF610_DAC_DAT0 (int) ; 
 struct vf610_dac* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_write_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int val, int val2,
			long mask)
{
	struct vf610_dac *info = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		writel(VF610_DAC_DAT0(val), info->regs);
		mutex_unlock(&indio_dev->mlock);
		return 0;

	default:
		return -EINVAL;
	}
}