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
struct srf04_data {int /*<<< orphan*/  falling; void* ts_falling; int /*<<< orphan*/  rising; void* ts_rising; int /*<<< orphan*/  gpiod_echo; } ;
struct iio_dev {int dummy; } ;
typedef  void* ktime_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 struct srf04_data* iio_priv (struct iio_dev*) ; 
 void* ktime_get () ; 

__attribute__((used)) static irqreturn_t srf04_handle_irq(int irq, void *dev_id)
{
	struct iio_dev *indio_dev = dev_id;
	struct srf04_data *data = iio_priv(indio_dev);
	ktime_t now = ktime_get();

	if (gpiod_get_value(data->gpiod_echo)) {
		data->ts_rising = now;
		complete(&data->rising);
	} else {
		data->ts_falling = now;
		complete(&data->falling);
	}

	return IRQ_HANDLED;
}