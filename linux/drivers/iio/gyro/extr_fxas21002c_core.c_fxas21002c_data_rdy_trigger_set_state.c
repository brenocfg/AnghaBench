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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct fxas21002c_data {int /*<<< orphan*/ * regmap_fields; } ;

/* Variables and functions */
 size_t F_INT_EN_DRDY ; 
 struct fxas21002c_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_data_rdy_trigger_set_state(struct iio_trigger *trig,
						 bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct fxas21002c_data *data = iio_priv(indio_dev);

	return regmap_field_write(data->regmap_fields[F_INT_EN_DRDY], state);
}