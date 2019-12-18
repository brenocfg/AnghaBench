#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_21__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct pinctrl_xway_soc {int pin_count; int /*<<< orphan*/  num_exin; int /*<<< orphan*/  exin; int /*<<< orphan*/  num_funcs; int /*<<< orphan*/  funcs; int /*<<< orphan*/  num_grps; int /*<<< orphan*/  grps; int /*<<< orphan*/  mfp; } ;
struct pinctrl_pin_desc {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_22__ {char* name; scalar_t__ number; } ;
struct TYPE_20__ {int ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; TYPE_6__* parent; } ;
struct TYPE_19__ {int npins; int /*<<< orphan*/  base; } ;
struct TYPE_18__ {int num_pads; int num_mfp; int /*<<< orphan*/  pctrl; int /*<<< orphan*/  num_exin; int /*<<< orphan*/  exin; int /*<<< orphan*/  num_funcs; int /*<<< orphan*/  funcs; int /*<<< orphan*/  num_grps; int /*<<< orphan*/  grps; int /*<<< orphan*/  mfp; TYPE_8__* pads; int /*<<< orphan*/ * membase; } ;
struct TYPE_17__ {int npins; int /*<<< orphan*/  name; TYPE_8__* pins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO0 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct pinctrl_xway_soc danube_pinctrl ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int devm_gpiochip_add_data (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 char* devm_kasprintf (TYPE_6__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_8__* devm_kcalloc (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 int ltq_pinctrl_register (struct platform_device*,TYPE_2__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ xway_chip ; 
 TYPE_3__ xway_gpio_range ; 
 TYPE_2__ xway_info ; 
 int /*<<< orphan*/  xway_match ; 
 TYPE_1__ xway_pctrl_desc ; 

__attribute__((used)) static int pinmux_xway_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	const struct pinctrl_xway_soc *xway_soc;
	struct resource *res;
	int ret, i;

	/* get and remap our register range */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xway_info.membase[0] = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xway_info.membase[0]))
		return PTR_ERR(xway_info.membase[0]);

	match = of_match_device(xway_match, &pdev->dev);
	if (match)
		xway_soc = (const struct pinctrl_xway_soc *) match->data;
	else
		xway_soc = &danube_pinctrl;

	/* find out how many pads we have */
	xway_chip.ngpio = xway_soc->pin_count;

	/* load our pad descriptors */
	xway_info.pads = devm_kcalloc(&pdev->dev,
			xway_chip.ngpio, sizeof(struct pinctrl_pin_desc),
			GFP_KERNEL);
	if (!xway_info.pads)
		return -ENOMEM;

	for (i = 0; i < xway_chip.ngpio; i++) {
		char *name = devm_kasprintf(&pdev->dev, GFP_KERNEL, "io%d", i);

		if (!name)
			return -ENOMEM;

		xway_info.pads[i].number = GPIO0 + i;
		xway_info.pads[i].name = name;
	}
	xway_pctrl_desc.pins = xway_info.pads;

	/* setup the data needed by pinctrl */
	xway_pctrl_desc.name	= dev_name(&pdev->dev);
	xway_pctrl_desc.npins	= xway_chip.ngpio;

	xway_info.num_pads	= xway_chip.ngpio;
	xway_info.num_mfp	= xway_chip.ngpio;
	xway_info.mfp		= xway_soc->mfp;
	xway_info.grps		= xway_soc->grps;
	xway_info.num_grps	= xway_soc->num_grps;
	xway_info.funcs		= xway_soc->funcs;
	xway_info.num_funcs	= xway_soc->num_funcs;
	xway_info.exin		= xway_soc->exin;
	xway_info.num_exin	= xway_soc->num_exin;

	/* register with the generic lantiq layer */
	ret = ltq_pinctrl_register(pdev, &xway_info);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register pinctrl driver\n");
		return ret;
	}

	/* register the gpio chip */
	xway_chip.parent = &pdev->dev;
	xway_chip.owner = THIS_MODULE;
	xway_chip.of_node = pdev->dev.of_node;
	ret = devm_gpiochip_add_data(&pdev->dev, &xway_chip, NULL);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register gpio chip\n");
		return ret;
	}

	/*
	 * For DeviceTree-supported systems, the gpio core checks the
	 * pinctrl's device node for the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * for the driver. In this case the driver can skip ahead.
	 *
	 * In order to remain compatible with older, existing DeviceTree
	 * files which don't set the "gpio-ranges" property or systems that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	if (!of_property_read_bool(pdev->dev.of_node, "gpio-ranges")) {
		/* finish with registering the gpio range in pinctrl */
		xway_gpio_range.npins = xway_chip.ngpio;
		xway_gpio_range.base = xway_chip.base;
		pinctrl_add_gpio_range(xway_info.pctrl, &xway_gpio_range);
	}

	dev_info(&pdev->dev, "Init done\n");
	return 0;
}