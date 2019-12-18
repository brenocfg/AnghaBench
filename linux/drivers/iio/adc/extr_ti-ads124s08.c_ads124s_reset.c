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
struct iio_dev {int dummy; } ;
struct ads124s_private {scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS124S08_CMD_RESET ; 
 int ads124s_write_cmd (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 struct ads124s_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ads124s_reset(struct iio_dev *indio_dev)
{
	struct ads124s_private *priv = iio_priv(indio_dev);

	if (priv->reset_gpio) {
		gpiod_set_value(priv->reset_gpio, 0);
		udelay(200);
		gpiod_set_value(priv->reset_gpio, 1);
	} else {
		return ads124s_write_cmd(indio_dev, ADS124S08_CMD_RESET);
	}

	return 0;
}