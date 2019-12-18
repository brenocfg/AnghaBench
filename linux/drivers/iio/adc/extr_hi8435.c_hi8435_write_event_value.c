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
typedef  int u8 ;
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct hi8435_priv {int* threshold_hi; int* threshold_lo; int /*<<< orphan*/  lock; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HI8435_GOCENHYS_REG ; 
 int /*<<< orphan*/  HI8435_PSEN_REG ; 
 int /*<<< orphan*/  HI8435_SOCENHYS_REG ; 
 int IIO_EV_DIR_FALLING ; 
 int IIO_EV_DIR_RISING ; 
 int hi8435_readb (struct hi8435_priv*,int /*<<< orphan*/ ,int*) ; 
 int hi8435_readw (struct hi8435_priv*,int /*<<< orphan*/ ,int*) ; 
 int hi8435_writew (struct hi8435_priv*,int /*<<< orphan*/ ,int) ; 
 struct hi8435_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hi8435_write_event_value(struct iio_dev *idev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int val, int val2)
{
	struct hi8435_priv *priv = iio_priv(idev);
	int ret;
	u8 mode, psen;
	u16 reg;

	ret = hi8435_readb(priv, HI8435_PSEN_REG, &psen);
	if (ret < 0)
		return ret;

	/* Supply-Open or GND-Open sensing mode */
	mode = !!(psen & BIT(chan->channel / 8));

	ret = hi8435_readw(priv, mode ? HI8435_SOCENHYS_REG :
				 HI8435_GOCENHYS_REG, &reg);
	if (ret < 0)
		return ret;

	if (dir == IIO_EV_DIR_FALLING) {
		/* falling threshold range 2..21V, hysteresis minimum 2V */
		if (val < 2 || val > 21 || (val + 2) > priv->threshold_hi[mode])
			return -EINVAL;

		if (val == priv->threshold_lo[mode])
			return 0;

		priv->threshold_lo[mode] = val;

		/* hysteresis must not be odd */
		if ((priv->threshold_hi[mode] - priv->threshold_lo[mode]) % 2)
			priv->threshold_hi[mode]--;
	} else if (dir == IIO_EV_DIR_RISING) {
		/* rising threshold range 3..22V, hysteresis minimum 2V */
		if (val < 3 || val > 22 || val < (priv->threshold_lo[mode] + 2))
			return -EINVAL;

		if (val == priv->threshold_hi[mode])
			return 0;

		priv->threshold_hi[mode] = val;

		/* hysteresis must not be odd */
		if ((priv->threshold_hi[mode] - priv->threshold_lo[mode]) % 2)
			priv->threshold_lo[mode]++;
	}

	/* program thresholds */
	mutex_lock(&priv->lock);

	ret = hi8435_readw(priv, mode ? HI8435_SOCENHYS_REG :
				 HI8435_GOCENHYS_REG, &reg);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	/* hysteresis */
	reg = priv->threshold_hi[mode] - priv->threshold_lo[mode];
	reg <<= 8;
	/* threshold center */
	reg |= (priv->threshold_hi[mode] + priv->threshold_lo[mode]);

	ret = hi8435_writew(priv, mode ? HI8435_SOCENHYS_REG :
				  HI8435_GOCENHYS_REG, reg);

	mutex_unlock(&priv->lock);

	return ret;
}