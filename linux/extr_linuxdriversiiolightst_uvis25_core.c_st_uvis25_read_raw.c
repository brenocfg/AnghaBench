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
struct st_uvis25_hw {int /*<<< orphan*/  irq; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 128 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct st_uvis25_hw* iio_priv (struct iio_dev*) ; 
 int st_uvis25_read_oneshot (struct st_uvis25_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int st_uvis25_read_raw(struct iio_dev *iio_dev,
			      struct iio_chan_spec const *ch,
			      int *val, int *val2, long mask)
{
	int ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	if (ret)
		return ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED: {
		struct st_uvis25_hw *hw = iio_priv(iio_dev);

		/*
		 * mask irq line during oneshot read since the sensor
		 * does not export the capability to disable data-ready line
		 * in the register map and it is enabled by default.
		 * If the line is unmasked during read_raw() it will be set
		 * active and never reset since the trigger is disabled
		 */
		if (hw->irq > 0)
			disable_irq(hw->irq);
		ret = st_uvis25_read_oneshot(hw, ch->address, val);
		if (hw->irq > 0)
			enable_irq(hw->irq);
		break;
	}
	default:
		ret = -EINVAL;
		break;
	}

	iio_device_release_direct_mode(iio_dev);

	return ret;
}