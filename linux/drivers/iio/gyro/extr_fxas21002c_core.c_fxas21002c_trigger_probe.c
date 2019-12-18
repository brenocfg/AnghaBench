#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device_node* of_node; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct fxas21002c_data {int irq; TYPE_3__* dready_trig; int /*<<< orphan*/ * regmap_fields; int /*<<< orphan*/  regmap; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {struct device* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t F_INT_CFG_DRDY ; 
 size_t F_IPOL ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 TYPE_3__* devm_iio_trigger_alloc (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (struct device*,TYPE_3__*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  fxas21002c_data_rdy_handler ; 
 int /*<<< orphan*/  fxas21002c_data_rdy_thread ; 
 int /*<<< orphan*/  fxas21002c_trigger_ops ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int of_irq_get_byname (struct device_node*,char*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fxas21002c_trigger_probe(struct fxas21002c_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct device_node *np = indio_dev->dev.of_node;
	unsigned long irq_trig;
	bool irq_open_drain;
	int irq1;
	int ret;

	if (!data->irq)
		return 0;

	irq1 = of_irq_get_byname(np, "INT1");

	if (irq1 == data->irq) {
		dev_info(dev, "using interrupt line INT1\n");
		ret = regmap_field_write(data->regmap_fields[F_INT_CFG_DRDY],
					 1);
		if (ret < 0)
			return ret;
	}

	dev_info(dev, "using interrupt line INT2\n");

	irq_open_drain = of_property_read_bool(np, "drive-open-drain");

	data->dready_trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
	if (!data->dready_trig)
		return -ENOMEM;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(data->irq));

	if (irq_trig == IRQF_TRIGGER_RISING) {
		ret = regmap_field_write(data->regmap_fields[F_IPOL], 1);
		if (ret < 0)
			return ret;
	}

	if (irq_open_drain)
		irq_trig |= IRQF_SHARED;

	ret = devm_request_threaded_irq(dev, data->irq,
					fxas21002c_data_rdy_handler,
					fxas21002c_data_rdy_thread,
					irq_trig, "fxas21002c_data_ready",
					indio_dev);
	if (ret < 0)
		return ret;

	data->dready_trig->dev.parent = dev;
	data->dready_trig->ops = &fxas21002c_trigger_ops;
	iio_trigger_set_drvdata(data->dready_trig, indio_dev);

	return devm_iio_trigger_register(dev, data->dready_trig);
}