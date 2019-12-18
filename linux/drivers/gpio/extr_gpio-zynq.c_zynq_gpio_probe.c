#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct gpio_irq_chip {int num_parents; int* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/ * chip; } ;
struct gpio_chip {struct gpio_irq_chip irq; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  set; int /*<<< orphan*/  get; TYPE_2__* parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct zynq_gpio {scalar_t__ irq; scalar_t__ clk; scalar_t__ base_addr; TYPE_1__* p_data; struct gpio_chip chip; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_11__ {int max_bank; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ ZYNQ_GPIO_INTDIS_OFFSET (int) ; 
 int /*<<< orphan*/  ZYNQ_GPIO_IXR_DISABLE_ALL ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 scalar_t__ devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct zynq_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (struct gpio_chip*,struct zynq_gpio*) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynq_gpio*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynq_gpio_dir_in ; 
 int /*<<< orphan*/  zynq_gpio_dir_out ; 
 int /*<<< orphan*/  zynq_gpio_edge_irqchip ; 
 int /*<<< orphan*/  zynq_gpio_free ; 
 int /*<<< orphan*/  zynq_gpio_get_direction ; 
 int /*<<< orphan*/  zynq_gpio_get_value ; 
 int /*<<< orphan*/  zynq_gpio_irqhandler ; 
 int /*<<< orphan*/  zynq_gpio_of_match ; 
 int /*<<< orphan*/  zynq_gpio_request ; 
 int /*<<< orphan*/  zynq_gpio_set_value ; 

__attribute__((used)) static int zynq_gpio_probe(struct platform_device *pdev)
{
	int ret, bank_num;
	struct zynq_gpio *gpio;
	struct gpio_chip *chip;
	struct gpio_irq_chip *girq;
	const struct of_device_id *match;

	gpio = devm_kzalloc(&pdev->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	match = of_match_node(zynq_gpio_of_match, pdev->dev.of_node);
	if (!match) {
		dev_err(&pdev->dev, "of_match_node() failed\n");
		return -EINVAL;
	}
	gpio->p_data = match->data;
	platform_set_drvdata(pdev, gpio);

	gpio->base_addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gpio->base_addr))
		return PTR_ERR(gpio->base_addr);

	gpio->irq = platform_get_irq(pdev, 0);
	if (gpio->irq < 0)
		return gpio->irq;

	/* configure the gpio chip */
	chip = &gpio->chip;
	chip->label = gpio->p_data->label;
	chip->owner = THIS_MODULE;
	chip->parent = &pdev->dev;
	chip->get = zynq_gpio_get_value;
	chip->set = zynq_gpio_set_value;
	chip->request = zynq_gpio_request;
	chip->free = zynq_gpio_free;
	chip->direction_input = zynq_gpio_dir_in;
	chip->direction_output = zynq_gpio_dir_out;
	chip->get_direction = zynq_gpio_get_direction;
	chip->base = of_alias_get_id(pdev->dev.of_node, "gpio");
	chip->ngpio = gpio->p_data->ngpio;

	/* Retrieve GPIO clock */
	gpio->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(gpio->clk)) {
		dev_err(&pdev->dev, "input clock not found.\n");
		return PTR_ERR(gpio->clk);
	}
	ret = clk_prepare_enable(gpio->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		goto err_pm_dis;

	/* disable interrupts for all banks */
	for (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++)
		writel_relaxed(ZYNQ_GPIO_IXR_DISABLE_ALL, gpio->base_addr +
			       ZYNQ_GPIO_INTDIS_OFFSET(bank_num));

	/* Set up the GPIO irqchip */
	girq = &chip->irq;
	girq->chip = &zynq_gpio_edge_irqchip;
	girq->parent_handler = zynq_gpio_irqhandler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(&pdev->dev, 1,
				     sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents) {
		ret = -ENOMEM;
		goto err_pm_put;
	}
	girq->parents[0] = gpio->irq;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	/* report a bug if gpio chip registration fails */
	ret = gpiochip_add_data(chip, gpio);
	if (ret) {
		dev_err(&pdev->dev, "Failed to add gpio chip\n");
		goto err_pm_put;
	}

	pm_runtime_put(&pdev->dev);

	return 0;

err_pm_put:
	pm_runtime_put(&pdev->dev);
err_pm_dis:
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(gpio->clk);

	return ret;
}