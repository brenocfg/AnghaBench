#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {int edge_irq; TYPE_5__* trig; int /*<<< orphan*/  irq; TYPE_4__* sensor_settings; scalar_t__ int_pin_open_drain; int /*<<< orphan*/  dev; } ;
struct iio_trigger_ops {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; TYPE_1__ dev; struct iio_trigger_ops const* ops; } ;
struct TYPE_13__ {scalar_t__ addr; } ;
struct TYPE_14__ {TYPE_2__ stat_drdy; int /*<<< orphan*/  mask_ihl; int /*<<< orphan*/  addr_ihl; } ;
struct TYPE_15__ {TYPE_3__ drdy_irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_5__*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 TYPE_5__* iio_trigger_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_free (TYPE_5__*) ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_5__*) ; 
 int iio_trigger_register (TYPE_5__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_5__*,struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  st_sensors_irq_handler ; 
 int /*<<< orphan*/  st_sensors_irq_thread ; 
 int st_sensors_write_data_with_mask (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int st_sensors_allocate_trigger(struct iio_dev *indio_dev,
				const struct iio_trigger_ops *trigger_ops)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	unsigned long irq_trig;
	int err;

	sdata->trig = iio_trigger_alloc("%s-trigger", indio_dev->name);
	if (sdata->trig == NULL) {
		dev_err(&indio_dev->dev, "failed to allocate iio trigger.\n");
		return -ENOMEM;
	}

	iio_trigger_set_drvdata(sdata->trig, indio_dev);
	sdata->trig->ops = trigger_ops;
	sdata->trig->dev.parent = sdata->dev;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(sdata->irq));
	/*
	 * If the IRQ is triggered on falling edge, we need to mark the
	 * interrupt as active low, if the hardware supports this.
	 */
	switch(irq_trig) {
	case IRQF_TRIGGER_FALLING:
	case IRQF_TRIGGER_LOW:
		if (!sdata->sensor_settings->drdy_irq.addr_ihl) {
			dev_err(&indio_dev->dev,
				"falling/low specified for IRQ "
				"but hardware supports only rising/high: "
				"will request rising/high\n");
			if (irq_trig == IRQF_TRIGGER_FALLING)
				irq_trig = IRQF_TRIGGER_RISING;
			if (irq_trig == IRQF_TRIGGER_LOW)
				irq_trig = IRQF_TRIGGER_HIGH;
		} else {
			/* Set up INT active low i.e. falling edge */
			err = st_sensors_write_data_with_mask(indio_dev,
				sdata->sensor_settings->drdy_irq.addr_ihl,
				sdata->sensor_settings->drdy_irq.mask_ihl, 1);
			if (err < 0)
				goto iio_trigger_free;
			dev_info(&indio_dev->dev,
				 "interrupts on the falling edge or "
				 "active low level\n");
		}
		break;
	case IRQF_TRIGGER_RISING:
		dev_info(&indio_dev->dev,
			 "interrupts on the rising edge\n");
		break;
	case IRQF_TRIGGER_HIGH:
		dev_info(&indio_dev->dev,
			 "interrupts active high level\n");
		break;
	default:
		/* This is the most preferred mode, if possible */
		dev_err(&indio_dev->dev,
			"unsupported IRQ trigger specified (%lx), enforce "
			"rising edge\n", irq_trig);
		irq_trig = IRQF_TRIGGER_RISING;
	}

	/* Tell the interrupt handler that we're dealing with edges */
	if (irq_trig == IRQF_TRIGGER_FALLING ||
	    irq_trig == IRQF_TRIGGER_RISING)
		sdata->edge_irq = true;
	else
		/*
		 * If we're not using edges (i.e. level interrupts) we
		 * just mask off the IRQ, handle one interrupt, then
		 * if the line is still low, we return to the
		 * interrupt handler top half again and start over.
		 */
		irq_trig |= IRQF_ONESHOT;

	/*
	 * If the interrupt pin is Open Drain, by definition this
	 * means that the interrupt line may be shared with other
	 * peripherals. But to do this we also need to have a status
	 * register and mask to figure out if this sensor was firing
	 * the IRQ or not, so we can tell the interrupt handle that
	 * it was "our" interrupt.
	 */
	if (sdata->int_pin_open_drain &&
	    sdata->sensor_settings->drdy_irq.stat_drdy.addr)
		irq_trig |= IRQF_SHARED;

	err = request_threaded_irq(sdata->irq,
				   st_sensors_irq_handler,
				   st_sensors_irq_thread,
				   irq_trig,
				   sdata->trig->name,
				   sdata->trig);
	if (err) {
		dev_err(&indio_dev->dev, "failed to request trigger IRQ.\n");
		goto iio_trigger_free;
	}

	err = iio_trigger_register(sdata->trig);
	if (err < 0) {
		dev_err(&indio_dev->dev, "failed to register iio trigger.\n");
		goto iio_trigger_register_error;
	}
	indio_dev->trig = iio_trigger_get(sdata->trig);

	return 0;

iio_trigger_register_error:
	free_irq(sdata->irq, sdata->trig);
iio_trigger_free:
	iio_trigger_free(sdata->trig);
	return err;
}