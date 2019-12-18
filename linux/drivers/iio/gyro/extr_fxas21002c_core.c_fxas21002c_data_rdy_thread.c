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
struct fxas21002c_data {int /*<<< orphan*/  dready_trig; int /*<<< orphan*/ * regmap_fields; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t F_SRC_DRDY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct fxas21002c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t fxas21002c_data_rdy_thread(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct fxas21002c_data *data = iio_priv(indio_dev);
	unsigned int data_ready;
	int ret;

	ret = regmap_field_read(data->regmap_fields[F_SRC_DRDY], &data_ready);
	if (ret < 0)
		return IRQ_NONE;

	if (!data_ready)
		return IRQ_NONE;

	iio_trigger_poll_chained(data->dready_trig);

	return IRQ_HANDLED;
}