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
struct iio_dev {int dummy; } ;
struct apds9960_data {int /*<<< orphan*/  regmap; scalar_t__ pxs_int; scalar_t__ als_int; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_CICLEAR ; 
 int /*<<< orphan*/  APDS9960_REG_PICLEAR ; 
 int /*<<< orphan*/  APDS9960_REG_STATUS ; 
 int APDS9960_REG_STATUS_ALS_INT ; 
 int APDS9960_REG_STATUS_GINT ; 
 int APDS9960_REG_STATUS_PS_INT ; 
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 int /*<<< orphan*/  IIO_PROXIMITY ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  apds9960_read_gesture_fifo (struct apds9960_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct apds9960_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t apds9960_interrupt_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct apds9960_data *data = iio_priv(indio_dev);
	int ret, status;

	ret = regmap_read(data->regmap, APDS9960_REG_STATUS, &status);
	if (ret < 0) {
		dev_err(&data->client->dev, "irq status reg read failed\n");
		return IRQ_HANDLED;
	}

	if ((status & APDS9960_REG_STATUS_ALS_INT) && data->als_int) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_EITHER),
			       iio_get_time_ns(indio_dev));
		regmap_write(data->regmap, APDS9960_REG_CICLEAR, 1);
	}

	if ((status & APDS9960_REG_STATUS_PS_INT) && data->pxs_int) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_EITHER),
			       iio_get_time_ns(indio_dev));
		regmap_write(data->regmap, APDS9960_REG_PICLEAR, 1);
	}

	if (status & APDS9960_REG_STATUS_GINT)
		apds9960_read_gesture_fifo(data);

	return IRQ_HANDLED;
}