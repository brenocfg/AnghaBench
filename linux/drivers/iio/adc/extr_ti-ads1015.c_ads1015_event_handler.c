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
typedef  int /*<<< orphan*/  u64 ;
struct iio_dev {int dummy; } ;
struct ads1015_data {scalar_t__ comp_mode; int /*<<< orphan*/  event_channel; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 scalar_t__ ADS1015_CFG_COMP_MODE_TRAD ; 
 int /*<<< orphan*/  ADS1015_CONV_REG ; 
 int IIO_EV_DIR_EITHER ; 
 int IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ads1015_event_channel_enabled (struct ads1015_data*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t ads1015_event_handler(int irq, void *priv)
{
	struct iio_dev *indio_dev = priv;
	struct ads1015_data *data = iio_priv(indio_dev);
	int val;
	int ret;

	/* Clear the latched ALERT/RDY pin */
	ret = regmap_read(data->regmap, ADS1015_CONV_REG, &val);
	if (ret)
		return IRQ_HANDLED;

	if (ads1015_event_channel_enabled(data)) {
		enum iio_event_direction dir;
		u64 code;

		dir = data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD ?
					IIO_EV_DIR_RISING : IIO_EV_DIR_EITHER;
		code = IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, data->event_channel,
					IIO_EV_TYPE_THRESH, dir);
		iio_push_event(indio_dev, code, iio_get_time_ns(indio_dev));
	}

	return IRQ_HANDLED;
}