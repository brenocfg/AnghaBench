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
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct pinctrl_dev {int dummy; } ;
struct pinctrl_desc {void* npins; void* pins; } ;
struct TYPE_2__ {int can_sleep; int base; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  label; } ;
struct lochnagar_pin_priv {TYPE_1__ gpio_chip; struct device* dev; void* npins; void* pins; void* ngroups; void* groups; void* nfuncs; void* funcs; struct lochnagar* lochnagar; } ;
struct lochnagar {int type; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl_dev*) ; 
#define  LOCHNAGAR1 129 
 int /*<<< orphan*/  LOCHNAGAR1_PIN_NUM_GPIOS ; 
#define  LOCHNAGAR2 128 
 int /*<<< orphan*/  LOCHNAGAR2_PIN_NUM_GPIOS ; 
 int PTR_ERR (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct lochnagar* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct lochnagar_pin_priv*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl_dev* devm_pinctrl_register (struct device*,struct pinctrl_desc*,struct lochnagar_pin_priv*) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 void* lochnagar1_funcs ; 
 void* lochnagar1_groups ; 
 void* lochnagar1_pins ; 
 void* lochnagar2_funcs ; 
 void* lochnagar2_groups ; 
 void* lochnagar2_pins ; 
 int lochnagar_fill_func_groups (struct lochnagar_pin_priv*) ; 
 int /*<<< orphan*/  lochnagar_gpio_direction_out ; 
 int /*<<< orphan*/  lochnagar_gpio_set ; 
 struct pinctrl_desc lochnagar_pin_desc ; 

__attribute__((used)) static int lochnagar_pin_probe(struct platform_device *pdev)
{
	struct lochnagar *lochnagar = dev_get_drvdata(pdev->dev.parent);
	struct lochnagar_pin_priv *priv;
	struct pinctrl_desc *desc;
	struct pinctrl_dev *pctl;
	struct device *dev = &pdev->dev;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;
	priv->lochnagar = lochnagar;

	desc = devm_kzalloc(dev, sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	*desc = lochnagar_pin_desc;

	priv->gpio_chip.label = dev_name(dev);
	priv->gpio_chip.request = gpiochip_generic_request;
	priv->gpio_chip.free = gpiochip_generic_free;
	priv->gpio_chip.direction_output = lochnagar_gpio_direction_out;
	priv->gpio_chip.set = lochnagar_gpio_set;
	priv->gpio_chip.can_sleep = true;
	priv->gpio_chip.parent = dev;
	priv->gpio_chip.base = -1;
#ifdef CONFIG_OF_GPIO
	priv->gpio_chip.of_node = dev->of_node;
#endif

	switch (lochnagar->type) {
	case LOCHNAGAR1:
		priv->funcs = lochnagar1_funcs;
		priv->nfuncs = ARRAY_SIZE(lochnagar1_funcs);
		priv->pins = lochnagar1_pins;
		priv->npins = ARRAY_SIZE(lochnagar1_pins);
		priv->groups = lochnagar1_groups;
		priv->ngroups = ARRAY_SIZE(lochnagar1_groups);

		priv->gpio_chip.ngpio = LOCHNAGAR1_PIN_NUM_GPIOS;
		break;
	case LOCHNAGAR2:
		priv->funcs = lochnagar2_funcs;
		priv->nfuncs = ARRAY_SIZE(lochnagar2_funcs);
		priv->pins = lochnagar2_pins;
		priv->npins = ARRAY_SIZE(lochnagar2_pins);
		priv->groups = lochnagar2_groups;
		priv->ngroups = ARRAY_SIZE(lochnagar2_groups);

		priv->gpio_chip.ngpio = LOCHNAGAR2_PIN_NUM_GPIOS;
		break;
	default:
		dev_err(dev, "Unknown Lochnagar type: %d\n", lochnagar->type);
		return -EINVAL;
	}

	ret = lochnagar_fill_func_groups(priv);
	if (ret < 0)
		return ret;

	desc->pins = priv->pins;
	desc->npins = priv->npins;

	pctl = devm_pinctrl_register(dev, desc, priv);
	if (IS_ERR(pctl)) {
		ret = PTR_ERR(pctl);
		dev_err(priv->dev, "Failed to register pinctrl: %d\n", ret);
		return ret;
	}

	ret = devm_gpiochip_add_data(dev, &priv->gpio_chip, priv);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register gpiochip: %d\n", ret);
		return ret;
	}

	return 0;
}