#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tilcdc_module {int dummy; } ;
struct tfp410_module {scalar_t__ gpio; int /*<<< orphan*/  i2c; struct tilcdc_module base; } ;
struct TYPE_5__ {struct tilcdc_module* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pinctrl {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct tfp410_module* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl* devm_pinctrl_get_select_default (TYPE_1__*) ; 
 int gpio_request (scalar_t__,char*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_find_i2c_adapter_by_node (struct device_node*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 scalar_t__ of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfp410_module_ops ; 
 int /*<<< orphan*/  tilcdc_module_cleanup (struct tilcdc_module*) ; 
 int /*<<< orphan*/  tilcdc_module_init (struct tilcdc_module*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tfp410_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device_node *i2c_node;
	struct tfp410_module *tfp410_mod;
	struct tilcdc_module *mod;
	struct pinctrl *pinctrl;
	uint32_t i2c_phandle;
	int ret = -EINVAL;

	/* bail out early if no DT data: */
	if (!node) {
		dev_err(&pdev->dev, "device-tree data is missing\n");
		return -ENXIO;
	}

	tfp410_mod = devm_kzalloc(&pdev->dev, sizeof(*tfp410_mod), GFP_KERNEL);
	if (!tfp410_mod)
		return -ENOMEM;

	mod = &tfp410_mod->base;
	pdev->dev.platform_data = mod;

	tilcdc_module_init(mod, "tfp410", &tfp410_module_ops);

	pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
	if (IS_ERR(pinctrl))
		dev_warn(&pdev->dev, "pins are not configured\n");

	if (of_property_read_u32(node, "i2c", &i2c_phandle)) {
		dev_err(&pdev->dev, "could not get i2c bus phandle\n");
		goto fail;
	}

	i2c_node = of_find_node_by_phandle(i2c_phandle);
	if (!i2c_node) {
		dev_err(&pdev->dev, "could not get i2c bus node\n");
		goto fail;
	}

	tfp410_mod->i2c = of_find_i2c_adapter_by_node(i2c_node);
	if (!tfp410_mod->i2c) {
		dev_err(&pdev->dev, "could not get i2c\n");
		of_node_put(i2c_node);
		goto fail;
	}

	of_node_put(i2c_node);

	tfp410_mod->gpio = of_get_named_gpio_flags(node, "powerdn-gpio",
			0, NULL);
	if (tfp410_mod->gpio < 0) {
		dev_warn(&pdev->dev, "No power down GPIO\n");
	} else {
		ret = gpio_request(tfp410_mod->gpio, "DVI_PDn");
		if (ret) {
			dev_err(&pdev->dev, "could not get DVI_PDn gpio\n");
			goto fail_adapter;
		}
	}

	return 0;

fail_adapter:
	i2c_put_adapter(tfp410_mod->i2c);

fail:
	tilcdc_module_cleanup(mod);
	return ret;
}