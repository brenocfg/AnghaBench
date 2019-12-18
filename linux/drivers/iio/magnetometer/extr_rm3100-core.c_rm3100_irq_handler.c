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
struct rm3100_data {int /*<<< orphan*/  drdy_trig; int /*<<< orphan*/  measuring_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {int currentmode; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
#define  INDIO_BUFFER_TRIGGERED 129 
#define  INDIO_DIRECT_MODE 128 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rm3100_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rm3100_irq_handler(int irq, void *d)
{
	struct iio_dev *indio_dev = d;
	struct rm3100_data *data = iio_priv(indio_dev);

	switch (indio_dev->currentmode) {
	case INDIO_DIRECT_MODE:
		complete(&data->measuring_done);
		break;
	case INDIO_BUFFER_TRIGGERED:
		iio_trigger_poll(data->drdy_trig);
		break;
	default:
		dev_err(indio_dev->dev.parent,
			"device mode out of control, current mode: %d",
			indio_dev->currentmode);
	}

	return IRQ_WAKE_THREAD;
}