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
struct mpu3050 {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MPU3050_INT_STATUS ; 
 unsigned int MPU3050_INT_STATUS_RAW_RDY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (void*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t mpu3050_irq_thread(int irq, void *p)
{
	struct iio_trigger *trig = p;
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);
	unsigned int val;
	int ret;

	/* ACK IRQ and check if it was from us */
	ret = regmap_read(mpu3050->map, MPU3050_INT_STATUS, &val);
	if (ret) {
		dev_err(mpu3050->dev, "error reading IRQ status\n");
		return IRQ_HANDLED;
	}
	if (!(val & MPU3050_INT_STATUS_RAW_RDY))
		return IRQ_NONE;

	iio_trigger_poll_chained(p);

	return IRQ_HANDLED;
}