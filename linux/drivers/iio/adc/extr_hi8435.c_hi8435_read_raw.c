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
typedef  int u32 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct hi8435_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HI8435_SO31_0_REG ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int hi8435_readl (struct hi8435_priv*,int /*<<< orphan*/ ,int*) ; 
 struct hi8435_priv* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int hi8435_read_raw(struct iio_dev *idev,
			   const struct iio_chan_spec *chan,
			   int *val, int *val2, long mask)
{
	struct hi8435_priv *priv = iio_priv(idev);
	u32 tmp;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = hi8435_readl(priv, HI8435_SO31_0_REG, &tmp);
		if (ret < 0)
			return ret;
		*val = !!(tmp & BIT(chan->channel));
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}