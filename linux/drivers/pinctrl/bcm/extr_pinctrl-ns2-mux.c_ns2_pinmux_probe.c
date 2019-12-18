#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_pin_desc {TYPE_2__* drv_data; int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
struct ns2_pinctrl {void* pctl; void* num_functions; TYPE_2__* functions; void* num_groups; TYPE_2__* groups; void* pinconf_base; int /*<<< orphan*/  base1; void* base0; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pin; } ;
struct TYPE_7__ {unsigned int npins; struct pinctrl_pin_desc* pins; } ;

/* Variables and functions */
 void* ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct ns2_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ns2_mux_log_init (struct ns2_pinctrl*) ; 
 TYPE_2__* ns2_pin_functions ; 
 TYPE_2__* ns2_pin_groups ; 
 TYPE_1__ ns2_pinctrl_desc ; 
 TYPE_2__* ns2_pins ; 
 void* pinctrl_register (TYPE_1__*,int /*<<< orphan*/ *,struct ns2_pinctrl*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ns2_pinctrl*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ns2_pinmux_probe(struct platform_device *pdev)
{
	struct ns2_pinctrl *pinctrl;
	struct resource *res;
	int i, ret;
	struct pinctrl_pin_desc *pins;
	unsigned int num_pins = ARRAY_SIZE(ns2_pins);

	pinctrl = devm_kzalloc(&pdev->dev, sizeof(*pinctrl), GFP_KERNEL);
	if (!pinctrl)
		return -ENOMEM;

	pinctrl->dev = &pdev->dev;
	platform_set_drvdata(pdev, pinctrl);
	spin_lock_init(&pinctrl->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pinctrl->base0 = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pinctrl->base0))
		return PTR_ERR(pinctrl->base0);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res)
		return -EINVAL;
	pinctrl->base1 = devm_ioremap_nocache(&pdev->dev, res->start,
					resource_size(res));
	if (!pinctrl->base1) {
		dev_err(&pdev->dev, "unable to map I/O space\n");
		return -ENOMEM;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	pinctrl->pinconf_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pinctrl->pinconf_base))
		return PTR_ERR(pinctrl->pinconf_base);

	ret = ns2_mux_log_init(pinctrl);
	if (ret) {
		dev_err(&pdev->dev, "unable to initialize IOMUX log\n");
		return ret;
	}

	pins = devm_kcalloc(&pdev->dev, num_pins, sizeof(*pins), GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	for (i = 0; i < num_pins; i++) {
		pins[i].number = ns2_pins[i].pin;
		pins[i].name = ns2_pins[i].name;
		pins[i].drv_data = &ns2_pins[i];
	}

	pinctrl->groups = ns2_pin_groups;
	pinctrl->num_groups = ARRAY_SIZE(ns2_pin_groups);
	pinctrl->functions = ns2_pin_functions;
	pinctrl->num_functions = ARRAY_SIZE(ns2_pin_functions);
	ns2_pinctrl_desc.pins = pins;
	ns2_pinctrl_desc.npins = num_pins;

	pinctrl->pctl = pinctrl_register(&ns2_pinctrl_desc, &pdev->dev,
			pinctrl);
	if (IS_ERR(pinctrl->pctl)) {
		dev_err(&pdev->dev, "unable to register IOMUX pinctrl\n");
		return PTR_ERR(pinctrl->pctl);
	}

	return 0;
}