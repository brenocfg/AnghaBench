#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int base; int /*<<< orphan*/  owner; TYPE_1__* parent; int /*<<< orphan*/  label; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  ngpio; } ;
struct spear_spics {int last_off; TYPE_4__ chip; int /*<<< orphan*/  cs_enable_shift; int /*<<< orphan*/  cs_enable_mask; int /*<<< orphan*/  cs_value_bit; int /*<<< orphan*/  sw_enable_bit; int /*<<< orphan*/  perip_cfg; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_OF_GPIO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_4__*,struct spear_spics*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct spear_spics* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spear_spics*) ; 
 int /*<<< orphan*/  spics_direction_input ; 
 int /*<<< orphan*/  spics_direction_output ; 
 int /*<<< orphan*/  spics_free ; 
 int /*<<< orphan*/  spics_get_value ; 
 int /*<<< orphan*/  spics_request ; 
 int /*<<< orphan*/  spics_set_value ; 

__attribute__((used)) static int spics_gpio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct spear_spics *spics;
	struct resource *res;
	int ret;

	spics = devm_kzalloc(&pdev->dev, sizeof(*spics), GFP_KERNEL);
	if (!spics)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	spics->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(spics->base))
		return PTR_ERR(spics->base);

	if (of_property_read_u32(np, "st-spics,peripcfg-reg",
				&spics->perip_cfg))
		goto err_dt_data;
	if (of_property_read_u32(np, "st-spics,sw-enable-bit",
				&spics->sw_enable_bit))
		goto err_dt_data;
	if (of_property_read_u32(np, "st-spics,cs-value-bit",
				&spics->cs_value_bit))
		goto err_dt_data;
	if (of_property_read_u32(np, "st-spics,cs-enable-mask",
				&spics->cs_enable_mask))
		goto err_dt_data;
	if (of_property_read_u32(np, "st-spics,cs-enable-shift",
				&spics->cs_enable_shift))
		goto err_dt_data;

	platform_set_drvdata(pdev, spics);

	spics->chip.ngpio = NUM_OF_GPIO;
	spics->chip.base = -1;
	spics->chip.request = spics_request;
	spics->chip.free = spics_free;
	spics->chip.direction_input = spics_direction_input;
	spics->chip.direction_output = spics_direction_output;
	spics->chip.get = spics_get_value;
	spics->chip.set = spics_set_value;
	spics->chip.label = dev_name(&pdev->dev);
	spics->chip.parent = &pdev->dev;
	spics->chip.owner = THIS_MODULE;
	spics->last_off = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &spics->chip, spics);
	if (ret) {
		dev_err(&pdev->dev, "unable to add gpio chip\n");
		return ret;
	}

	dev_info(&pdev->dev, "spear spics registered\n");
	return 0;

err_dt_data:
	dev_err(&pdev->dev, "DT probe failed\n");
	return -EINVAL;
}