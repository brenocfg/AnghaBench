#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_uvis25_hw {TYPE_2__* trig; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned long IRQF_ONESHOT ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  ST_UVIS25_REG_CTRL3_ADDR ; 
 int /*<<< orphan*/  ST_UVIS25_REG_HL_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned long) ; 
 TYPE_2__* devm_iio_trigger_alloc (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (struct device*,TYPE_2__*) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct st_uvis25_hw*) ; 
 struct st_uvis25_hw* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_uvis25_trigger_handler_thread ; 

__attribute__((used)) static int st_uvis25_allocate_trigger(struct iio_dev *iio_dev)
{
	struct st_uvis25_hw *hw = iio_priv(iio_dev);
	struct device *dev = regmap_get_device(hw->regmap);
	bool irq_active_low = false;
	unsigned long irq_type;
	int err;

	irq_type = irqd_get_trigger_type(irq_get_irq_data(hw->irq));

	switch (irq_type) {
	case IRQF_TRIGGER_HIGH:
	case IRQF_TRIGGER_RISING:
		break;
	case IRQF_TRIGGER_LOW:
	case IRQF_TRIGGER_FALLING:
		irq_active_low = true;
		break;
	default:
		dev_info(dev, "mode %lx unsupported\n", irq_type);
		return -EINVAL;
	}

	err = regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL3_ADDR,
				 ST_UVIS25_REG_HL_MASK, irq_active_low);
	if (err < 0)
		return err;

	err = devm_request_threaded_irq(dev, hw->irq, NULL,
					st_uvis25_trigger_handler_thread,
					irq_type | IRQF_ONESHOT,
					iio_dev->name, hw);
	if (err) {
		dev_err(dev, "failed to request trigger irq %d\n",
			hw->irq);
		return err;
	}

	hw->trig = devm_iio_trigger_alloc(dev, "%s-trigger",
					  iio_dev->name);
	if (!hw->trig)
		return -ENOMEM;

	iio_trigger_set_drvdata(hw->trig, iio_dev);
	hw->trig->dev.parent = dev;

	return devm_iio_trigger_register(dev, hw->trig);
}