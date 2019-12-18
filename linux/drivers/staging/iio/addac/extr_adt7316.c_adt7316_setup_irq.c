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
struct iio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct adt7316_chip_info {int /*<<< orphan*/  config1; TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_INT_POLARITY ; 
 int IRQF_ONESHOT ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  adt7316_event_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 int irqd_get_trigger_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7316_setup_irq(struct iio_dev *indio_dev)
{
	struct adt7316_chip_info *chip = iio_priv(indio_dev);
	int irq_type, ret;

	irq_type = irqd_get_trigger_type(irq_get_irq_data(chip->bus.irq));

	switch (irq_type) {
	case IRQF_TRIGGER_HIGH:
	case IRQF_TRIGGER_RISING:
		break;
	case IRQF_TRIGGER_LOW:
	case IRQF_TRIGGER_FALLING:
		break;
	default:
		dev_info(&indio_dev->dev, "mode %d unsupported, using IRQF_TRIGGER_LOW\n",
			 irq_type);
		irq_type = IRQF_TRIGGER_LOW;
		break;
	}

	ret = devm_request_threaded_irq(&indio_dev->dev, chip->bus.irq,
					NULL, adt7316_event_handler,
					irq_type | IRQF_ONESHOT,
					indio_dev->name, indio_dev);
	if (ret) {
		dev_err(&indio_dev->dev, "failed to request irq %d\n",
			chip->bus.irq);
		return ret;
	}

	if (irq_type & IRQF_TRIGGER_HIGH)
		chip->config1 |= ADT7316_INT_POLARITY;

	return 0;
}