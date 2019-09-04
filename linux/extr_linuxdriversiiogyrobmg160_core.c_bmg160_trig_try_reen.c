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
struct device {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  regmap; scalar_t__ dready_trigger_on; } ;

/* Variables and functions */
 int BMG160_INT_MODE_LATCH_INT ; 
 int BMG160_INT_MODE_LATCH_RESET ; 
 int /*<<< orphan*/  BMG160_REG_INT_RST_LATCH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bmg160_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmg160_trig_try_reen(struct iio_trigger *trig)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmg160_data *data = iio_priv(indio_dev);
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	/* new data interrupts don't need ack */
	if (data->dready_trigger_on)
		return 0;

	/* Set latched mode interrupt and clear any latched interrupt */
	ret = regmap_write(data->regmap, BMG160_REG_INT_RST_LATCH,
			   BMG160_INT_MODE_LATCH_INT |
			   BMG160_INT_MODE_LATCH_RESET);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_rst_latch\n");
		return ret;
	}

	return 0;
}