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
struct bmi160_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int bmi160_enable_irq (int /*<<< orphan*/ ,int) ; 
 struct bmi160_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static int bmi160_data_rdy_trigger_set_state(struct iio_trigger *trig,
					     bool enable)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmi160_data *data = iio_priv(indio_dev);

	return bmi160_enable_irq(data->regmap, enable);
}