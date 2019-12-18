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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gpio_chip {int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; } ;
struct mlxbf_gpio_state {struct gpio_chip gc; scalar_t__ base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MLXBF_GPIO_NR ; 
 scalar_t__ MLXBF_GPIO_PIN_DIR_I ; 
 scalar_t__ MLXBF_GPIO_PIN_DIR_O ; 
 scalar_t__ MLXBF_GPIO_PIN_STATE ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int bgpio_init (struct gpio_chip*,struct device*,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct mlxbf_gpio_state*) ; 
 struct mlxbf_gpio_state* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mlxbf_gpio_state*) ; 

__attribute__((used)) static int mlxbf_gpio_probe(struct platform_device *pdev)
{
	struct mlxbf_gpio_state *gs;
	struct device *dev = &pdev->dev;
	struct gpio_chip *gc;
	int ret;

	gs = devm_kzalloc(&pdev->dev, sizeof(*gs), GFP_KERNEL);
	if (!gs)
		return -ENOMEM;

	gs->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gs->base))
		return PTR_ERR(gs->base);

	gc = &gs->gc;
	ret = bgpio_init(gc, dev, 8,
			 gs->base + MLXBF_GPIO_PIN_STATE,
			 NULL,
			 NULL,
			 gs->base + MLXBF_GPIO_PIN_DIR_O,
			 gs->base + MLXBF_GPIO_PIN_DIR_I,
			 0);
	if (ret)
		return -ENODEV;

	gc->owner = THIS_MODULE;
	gc->ngpio = MLXBF_GPIO_NR;

	ret = devm_gpiochip_add_data(dev, &gs->gc, gs);
	if (ret) {
		dev_err(&pdev->dev, "Failed adding memory mapped gpiochip\n");
		return ret;
	}

	platform_set_drvdata(pdev, gs);
	dev_info(&pdev->dev, "registered Mellanox BlueField GPIO");
	return 0;
}