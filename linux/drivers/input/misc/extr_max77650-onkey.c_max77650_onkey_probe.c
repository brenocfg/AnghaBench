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
struct regmap {int dummy; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct max77650_onkey {TYPE_2__* input; int /*<<< orphan*/  code; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; char* phys; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int ENODEV ; 
 int ENOMEM ; 
 unsigned int EV_KEY ; 
 unsigned int EV_SW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  MAX77650_ONKEY_MODE_MASK ; 
 int MAX77650_ONKEY_MODE_PUSH ; 
 int MAX77650_ONKEY_MODE_SLIDE ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GLBL ; 
 struct regmap* dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_input_allocate_device (struct device*) ; 
 struct max77650_onkey* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_any_context_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max77650_onkey*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max77650_onkey_falling ; 
 int /*<<< orphan*/  max77650_onkey_rising ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77650_onkey_probe(struct platform_device *pdev)
{
	int irq_r, irq_f, error, mode;
	struct max77650_onkey *onkey;
	struct device *dev, *parent;
	struct regmap *map;
	unsigned int type;

	dev = &pdev->dev;
	parent = dev->parent;

	map = dev_get_regmap(parent, NULL);
	if (!map)
		return -ENODEV;

	onkey = devm_kzalloc(dev, sizeof(*onkey), GFP_KERNEL);
	if (!onkey)
		return -ENOMEM;

	error = device_property_read_u32(dev, "linux,code", &onkey->code);
	if (error)
		onkey->code = KEY_POWER;

	if (device_property_read_bool(dev, "maxim,onkey-slide")) {
		mode = MAX77650_ONKEY_MODE_SLIDE;
		type = EV_SW;
	} else {
		mode = MAX77650_ONKEY_MODE_PUSH;
		type = EV_KEY;
	}

	error = regmap_update_bits(map, MAX77650_REG_CNFG_GLBL,
				   MAX77650_ONKEY_MODE_MASK, mode);
	if (error)
		return error;

	irq_f = platform_get_irq_byname(pdev, "nEN_F");
	if (irq_f < 0)
		return irq_f;

	irq_r = platform_get_irq_byname(pdev, "nEN_R");
	if (irq_r < 0)
		return irq_r;

	onkey->input = devm_input_allocate_device(dev);
	if (!onkey->input)
		return -ENOMEM;

	onkey->input->name = "max77650_onkey";
	onkey->input->phys = "max77650_onkey/input0";
	onkey->input->id.bustype = BUS_I2C;
	input_set_capability(onkey->input, type, onkey->code);

	error = devm_request_any_context_irq(dev, irq_f, max77650_onkey_falling,
					     IRQF_ONESHOT, "onkey-down", onkey);
	if (error < 0)
		return error;

	error = devm_request_any_context_irq(dev, irq_r, max77650_onkey_rising,
					     IRQF_ONESHOT, "onkey-up", onkey);
	if (error < 0)
		return error;

	return input_register_device(onkey->input);
}