#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gpio_chip {int base; int ngpio; int /*<<< orphan*/  owner; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  label; struct device* parent; } ;
struct ttl_module {struct gpio_chip gpio; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct janz_platform_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct janz_platform_data* dev_get_platdata (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ttl_module* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ttl_module*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttl_get_value ; 
 int /*<<< orphan*/  ttl_set_value ; 
 int /*<<< orphan*/  ttl_setup_device (struct ttl_module*) ; 

__attribute__((used)) static int ttl_probe(struct platform_device *pdev)
{
	struct janz_platform_data *pdata;
	struct device *dev = &pdev->dev;
	struct ttl_module *mod;
	struct gpio_chip *gpio;
	struct resource *res;
	int ret;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(dev, "no platform data\n");
		return -ENXIO;
	}

	mod = devm_kzalloc(dev, sizeof(*mod), GFP_KERNEL);
	if (!mod)
		return -ENOMEM;

	platform_set_drvdata(pdev, mod);
	spin_lock_init(&mod->lock);

	/* get access to the MODULbus registers for this module */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mod->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(mod->regs))
		return PTR_ERR(mod->regs);

	ttl_setup_device(mod);

	/* Initialize the GPIO data structures */
	gpio = &mod->gpio;
	gpio->parent = &pdev->dev;
	gpio->label = pdev->name;
	gpio->get = ttl_get_value;
	gpio->set = ttl_set_value;
	gpio->owner = THIS_MODULE;

	/* request dynamic allocation */
	gpio->base = -1;
	gpio->ngpio = 20;

	ret = devm_gpiochip_add_data(dev, gpio, NULL);
	if (ret) {
		dev_err(dev, "unable to add GPIO chip\n");
		return ret;
	}

	return 0;
}