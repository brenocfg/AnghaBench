#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct zpa2326_private {TYPE_2__* frequency; int /*<<< orphan*/  regmap; scalar_t__ waken; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {TYPE_1__ dev; } ;
struct iio_dev {int dummy; } ;
struct TYPE_6__ {int odr; } ;
struct TYPE_5__ {int odr; int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 scalar_t__ ZPA2326_CTRL_REG1_MASK_DATA_READY ; 
 int /*<<< orphan*/  ZPA2326_CTRL_REG1_REG ; 
 int ZPA2326_CTRL_REG3_ENABLE_MEAS ; 
 int /*<<< orphan*/  ZPA2326_CTRL_REG3_REG ; 
 int /*<<< orphan*/  ZPA2326_INT_SOURCE_REG ; 
 struct iio_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct zpa2326_private* iio_priv (struct iio_dev const*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*,...) ; 
 TYPE_3__* zpa2326_highest_frequency () ; 

__attribute__((used)) static int zpa2326_set_trigger_state(struct iio_trigger *trig, bool state)
{
	const struct iio_dev         *indio_dev = dev_get_drvdata(
							trig->dev.parent);
	const struct zpa2326_private *priv = iio_priv(indio_dev);
	int                           err;

	if (!state) {
		/*
		 * Switch trigger off : in case of failure, interrupt is left
		 * disabled in order to prevent handler from accessing released
		 * resources.
		 */
		unsigned int val;

		/*
		 * As device is working in continuous mode, handlers may be
		 * accessing resources we are currently freeing...
		 * Prevent this by disabling interrupt handlers and ensure
		 * the device will generate no more interrupts unless explicitly
		 * required to, i.e. by restoring back to default one shot mode.
		 */
		disable_irq(priv->irq);

		/*
		 * Disable continuous sampling mode to restore settings for
		 * one shot / direct sampling operations.
		 */
		err = regmap_write(priv->regmap, ZPA2326_CTRL_REG3_REG,
				   zpa2326_highest_frequency()->odr);
		if (err)
			return err;

		/*
		 * Now that device won't generate interrupts on its own,
		 * acknowledge any currently active interrupts (may happen on
		 * rare occasions while stopping continuous mode).
		 */
		err = regmap_read(priv->regmap, ZPA2326_INT_SOURCE_REG, &val);
		if (err < 0)
			return err;

		/*
		 * Re-enable interrupts only if we can guarantee the device will
		 * generate no more interrupts to prevent handlers from
		 * accessing released resources.
		 */
		enable_irq(priv->irq);

		zpa2326_dbg(indio_dev, "continuous mode stopped");
	} else {
		/*
		 * Switch trigger on : start continuous sampling at required
		 * frequency.
		 */

		if (priv->waken) {
			/* Enable interrupt if getting out of reset. */
			err = regmap_write(priv->regmap, ZPA2326_CTRL_REG1_REG,
					   (u8)
					   ~ZPA2326_CTRL_REG1_MASK_DATA_READY);
			if (err)
				return err;
		}

		/* Enable continuous sampling at specified frequency. */
		err = regmap_write(priv->regmap, ZPA2326_CTRL_REG3_REG,
				   ZPA2326_CTRL_REG3_ENABLE_MEAS |
				   priv->frequency->odr);
		if (err)
			return err;

		zpa2326_dbg(indio_dev, "continuous mode setup @%dHz",
			    priv->frequency->hz);
	}

	return 0;
}