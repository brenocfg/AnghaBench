#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qpnp_tm_chip {int /*<<< orphan*/ * tz_dev; scalar_t__ subtype; int /*<<< orphan*/  base; int /*<<< orphan*/ * adc; int /*<<< orphan*/  map; int /*<<< orphan*/  lock; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QPNP_TM_REG_SUBTYPE ; 
 int /*<<< orphan*/  QPNP_TM_REG_TYPE ; 
 scalar_t__ QPNP_TM_SUBTYPE_GEN1 ; 
 scalar_t__ QPNP_TM_SUBTYPE_GEN2 ; 
 scalar_t__ QPNP_TM_TYPE ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct qpnp_tm_chip*) ; 
 int /*<<< orphan*/ * devm_iio_channel_get (TYPE_1__*,char*) ; 
 struct qpnp_tm_chip* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qpnp_tm_chip*) ; 
 int /*<<< orphan*/ * devm_thermal_zone_of_sensor_register (TYPE_1__*,int /*<<< orphan*/ ,struct qpnp_tm_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int qpnp_tm_init (struct qpnp_tm_chip*) ; 
 int /*<<< orphan*/  qpnp_tm_isr ; 
 int qpnp_tm_read (struct qpnp_tm_chip*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qpnp_tm_sensor_ops ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qpnp_tm_probe(struct platform_device *pdev)
{
	struct qpnp_tm_chip *chip;
	struct device_node *node;
	u8 type, subtype;
	u32 res;
	int ret, irq;

	node = pdev->dev.of_node;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	dev_set_drvdata(&pdev->dev, chip);
	chip->dev = &pdev->dev;

	mutex_init(&chip->lock);

	chip->map = dev_get_regmap(pdev->dev.parent, NULL);
	if (!chip->map)
		return -ENXIO;

	ret = of_property_read_u32(node, "reg", &res);
	if (ret < 0)
		return ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	/* ADC based measurements are optional */
	chip->adc = devm_iio_channel_get(&pdev->dev, "thermal");
	if (IS_ERR(chip->adc)) {
		ret = PTR_ERR(chip->adc);
		chip->adc = NULL;
		if (ret == -EPROBE_DEFER)
			return ret;
	}

	chip->base = res;

	ret = qpnp_tm_read(chip, QPNP_TM_REG_TYPE, &type);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not read type\n");
		return ret;
	}

	ret = qpnp_tm_read(chip, QPNP_TM_REG_SUBTYPE, &subtype);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not read subtype\n");
		return ret;
	}

	if (type != QPNP_TM_TYPE || (subtype != QPNP_TM_SUBTYPE_GEN1
				     && subtype != QPNP_TM_SUBTYPE_GEN2)) {
		dev_err(&pdev->dev, "invalid type 0x%02x or subtype 0x%02x\n",
			type, subtype);
		return -ENODEV;
	}

	chip->subtype = subtype;

	/*
	 * Register the sensor before initializing the hardware to be able to
	 * read the trip points. get_temp() returns the default temperature
	 * before the hardware initialization is completed.
	 */
	chip->tz_dev = devm_thermal_zone_of_sensor_register(
		&pdev->dev, 0, chip, &qpnp_tm_sensor_ops);
	if (IS_ERR(chip->tz_dev)) {
		dev_err(&pdev->dev, "failed to register sensor\n");
		return PTR_ERR(chip->tz_dev);
	}

	ret = qpnp_tm_init(chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "init failed\n");
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL, qpnp_tm_isr,
					IRQF_ONESHOT, node->name, chip);
	if (ret < 0)
		return ret;

	thermal_zone_device_update(chip->tz_dev, THERMAL_EVENT_UNSPECIFIED);

	return 0;
}