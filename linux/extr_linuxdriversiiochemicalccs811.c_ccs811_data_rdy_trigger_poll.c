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
struct ccs811_data {int /*<<< orphan*/  drdy_trig; scalar_t__ drdy_trig_on; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct ccs811_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ccs811_data_rdy_trigger_poll(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct ccs811_data *data = iio_priv(indio_dev);

	if (data->drdy_trig_on)
		iio_trigger_poll(data->drdy_trig);

	return IRQ_HANDLED;
}