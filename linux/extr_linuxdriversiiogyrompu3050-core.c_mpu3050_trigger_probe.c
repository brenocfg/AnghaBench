#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mpu3050 {int irq_opendrain; int irq_actl; int irq_latch; int irq; TYPE_2__* trig; TYPE_7__* dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {TYPE_7__* parent; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_2__*) ; 
 int iio_trigger_register (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpu3050_irq_handler ; 
 int /*<<< orphan*/  mpu3050_irq_thread ; 
 int /*<<< orphan*/  mpu3050_trigger_ops ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int mpu3050_trigger_probe(struct iio_dev *indio_dev, int irq)
{
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);
	unsigned long irq_trig;
	int ret;

	mpu3050->trig = devm_iio_trigger_alloc(&indio_dev->dev,
					       "%s-dev%d",
					       indio_dev->name,
					       indio_dev->id);
	if (!mpu3050->trig)
		return -ENOMEM;

	/* Check if IRQ is open drain */
	if (of_property_read_bool(mpu3050->dev->of_node, "drive-open-drain"))
		mpu3050->irq_opendrain = true;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	/*
	 * Configure the interrupt generator hardware to supply whatever
	 * the interrupt is configured for, edges low/high level low/high,
	 * we can provide it all.
	 */
	switch (irq_trig) {
	case IRQF_TRIGGER_RISING:
		dev_info(&indio_dev->dev,
			 "pulse interrupts on the rising edge\n");
		break;
	case IRQF_TRIGGER_FALLING:
		mpu3050->irq_actl = true;
		dev_info(&indio_dev->dev,
			 "pulse interrupts on the falling edge\n");
		break;
	case IRQF_TRIGGER_HIGH:
		mpu3050->irq_latch = true;
		dev_info(&indio_dev->dev,
			 "interrupts active high level\n");
		/*
		 * With level IRQs, we mask the IRQ until it is processed,
		 * but with edge IRQs (pulses) we can queue several interrupts
		 * in the top half.
		 */
		irq_trig |= IRQF_ONESHOT;
		break;
	case IRQF_TRIGGER_LOW:
		mpu3050->irq_latch = true;
		mpu3050->irq_actl = true;
		irq_trig |= IRQF_ONESHOT;
		dev_info(&indio_dev->dev,
			 "interrupts active low level\n");
		break;
	default:
		/* This is the most preferred mode, if possible */
		dev_err(&indio_dev->dev,
			"unsupported IRQ trigger specified (%lx), enforce "
			"rising edge\n", irq_trig);
		irq_trig = IRQF_TRIGGER_RISING;
		break;
	}

	/* An open drain line can be shared with several devices */
	if (mpu3050->irq_opendrain)
		irq_trig |= IRQF_SHARED;

	ret = request_threaded_irq(irq,
				   mpu3050_irq_handler,
				   mpu3050_irq_thread,
				   irq_trig,
				   mpu3050->trig->name,
				   mpu3050->trig);
	if (ret) {
		dev_err(mpu3050->dev,
			"can't get IRQ %d, error %d\n", irq, ret);
		return ret;
	}

	mpu3050->irq = irq;
	mpu3050->trig->dev.parent = mpu3050->dev;
	mpu3050->trig->ops = &mpu3050_trigger_ops;
	iio_trigger_set_drvdata(mpu3050->trig, indio_dev);

	ret = iio_trigger_register(mpu3050->trig);
	if (ret)
		return ret;

	indio_dev->trig = iio_trigger_get(mpu3050->trig);

	return 0;
}