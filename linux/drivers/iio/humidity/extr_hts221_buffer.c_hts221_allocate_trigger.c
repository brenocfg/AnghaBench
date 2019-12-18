#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct st_sensors_platform_data {scalar_t__ open_drain; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  name; } ;
struct hts221_hw {TYPE_2__* trig; TYPE_4__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  regmap; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {scalar_t__ platform_data; struct device_node* of_node; } ;
struct TYPE_11__ {TYPE_4__* parent; } ;
struct TYPE_12__ {TYPE_1__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_HL_ADDR ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_HL_MASK ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_PP_OD_ADDR ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_PP_OD_MASK ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,unsigned long) ; 
 TYPE_2__* devm_iio_trigger_alloc (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (TYPE_4__*,TYPE_2__*) ; 
 int devm_request_threaded_irq (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct hts221_hw*) ; 
 int /*<<< orphan*/  hts221_trigger_handler_thread ; 
 int /*<<< orphan*/  hts221_trigger_ops ; 
 struct iio_dev* iio_priv_to_dev (struct hts221_hw*) ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hts221_allocate_trigger(struct hts221_hw *hw)
{
	struct iio_dev *iio_dev = iio_priv_to_dev(hw);
	bool irq_active_low = false, open_drain = false;
	struct device_node *np = hw->dev->of_node;
	struct st_sensors_platform_data *pdata;
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
		dev_info(hw->dev,
			 "mode %lx unsupported, using IRQF_TRIGGER_RISING\n",
			 irq_type);
		irq_type = IRQF_TRIGGER_RISING;
		break;
	}

	err = regmap_update_bits(hw->regmap, HTS221_REG_DRDY_HL_ADDR,
				 HTS221_REG_DRDY_HL_MASK,
				 FIELD_PREP(HTS221_REG_DRDY_HL_MASK,
					    irq_active_low));
	if (err < 0)
		return err;

	pdata = (struct st_sensors_platform_data *)hw->dev->platform_data;
	if ((np && of_property_read_bool(np, "drive-open-drain")) ||
	    (pdata && pdata->open_drain)) {
		irq_type |= IRQF_SHARED;
		open_drain = true;
	}

	err = regmap_update_bits(hw->regmap, HTS221_REG_DRDY_PP_OD_ADDR,
				 HTS221_REG_DRDY_PP_OD_MASK,
				 FIELD_PREP(HTS221_REG_DRDY_PP_OD_MASK,
					    open_drain));
	if (err < 0)
		return err;

	err = devm_request_threaded_irq(hw->dev, hw->irq, NULL,
					hts221_trigger_handler_thread,
					irq_type | IRQF_ONESHOT,
					hw->name, hw);
	if (err) {
		dev_err(hw->dev, "failed to request trigger irq %d\n",
			hw->irq);
		return err;
	}

	hw->trig = devm_iio_trigger_alloc(hw->dev, "%s-trigger",
					  iio_dev->name);
	if (!hw->trig)
		return -ENOMEM;

	iio_trigger_set_drvdata(hw->trig, iio_dev);
	hw->trig->ops = &hts221_trigger_ops;
	hw->trig->dev.parent = hw->dev;
	iio_dev->trig = iio_trigger_get(hw->trig);

	return devm_iio_trigger_register(hw->dev, hw->trig);
}