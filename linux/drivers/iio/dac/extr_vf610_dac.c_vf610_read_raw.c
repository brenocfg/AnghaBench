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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int VF610_DAC_DAT0 (int /*<<< orphan*/ ) ; 
 struct vf610_dac* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val, int *val2,
			long mask)
{
	struct vf610_dac *info = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*val = VF610_DAC_DAT0(readl(info->regs));
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		/*
		 * DACRFS is always 1 for valid reference and typical
		 * reference voltage as per Vybrid datasheet is 3.3V
		 * from section 9.1.2.1 of Vybrid datasheet
		 */
		*val = 3300 /* mV */;
		*val2 = 12;
		return IIO_VAL_FRACTIONAL_LOG2;

	default:
		return -EINVAL;
	}
}