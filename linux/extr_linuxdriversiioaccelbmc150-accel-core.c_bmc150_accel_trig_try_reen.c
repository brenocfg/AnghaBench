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
struct device {int dummy; } ;
struct bmc150_accel_trigger {struct bmc150_accel_data* data; } ;
struct bmc150_accel_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; struct bmc150_accel_trigger* triggers; } ;

/* Variables and functions */
 int BMC150_ACCEL_INT_MODE_LATCH_INT ; 
 int BMC150_ACCEL_INT_MODE_LATCH_RESET ; 
 int /*<<< orphan*/  BMC150_ACCEL_REG_INT_RST_LATCH ; 
 size_t BMC150_ACCEL_TRIGGER_DATA_READY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bmc150_accel_trigger* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmc150_accel_trig_try_reen(struct iio_trigger *trig)
{
	struct bmc150_accel_trigger *t = iio_trigger_get_drvdata(trig);
	struct bmc150_accel_data *data = t->data;
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	/* new data interrupts don't need ack */
	if (t == &t->data->triggers[BMC150_ACCEL_TRIGGER_DATA_READY])
		return 0;

	mutex_lock(&data->mutex);
	/* clear any latched interrupt */
	ret = regmap_write(data->regmap, BMC150_ACCEL_REG_INT_RST_LATCH,
			   BMC150_ACCEL_INT_MODE_LATCH_INT |
			   BMC150_ACCEL_INT_MODE_LATCH_RESET);
	mutex_unlock(&data->mutex);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_int_rst_latch\n");
		return ret;
	}

	return 0;
}