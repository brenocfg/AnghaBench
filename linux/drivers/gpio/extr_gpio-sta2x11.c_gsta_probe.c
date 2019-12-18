#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sta2x11_gpio_pdata {int /*<<< orphan*/ * pinconfig; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct gsta_gpio {int irq_base; int /*<<< orphan*/  gpio; int /*<<< orphan*/  lock; TYPE_1__** regs; TYPE_1__* reg_base; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ic; int /*<<< orphan*/  fimsc; int /*<<< orphan*/  rimsc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GSTA_NR_BLOCKS ; 
 int GSTA_NR_GPIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct sta2x11_gpio_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct gsta_gpio*) ; 
 int devm_irq_alloc_descs (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 struct gsta_gpio* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gsta_gpio*) ; 
 int gsta_alloc_irq_chip (struct gsta_gpio*) ; 
 int /*<<< orphan*/  gsta_gpio_handler ; 
 int /*<<< orphan*/  gsta_gpio_setup (struct gsta_gpio*) ; 
 int /*<<< orphan*/  gsta_set_config (struct gsta_gpio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gsta_gpio*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sta2x11_gpio_pdata*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsta_probe(struct platform_device *dev)
{
	int i, err;
	struct pci_dev *pdev;
	struct sta2x11_gpio_pdata *gpio_pdata;
	struct gsta_gpio *chip;

	pdev = *(struct pci_dev **)dev_get_platdata(&dev->dev);
	gpio_pdata = dev_get_platdata(&pdev->dev);

	if (gpio_pdata == NULL)
		dev_err(&dev->dev, "no gpio config\n");
	pr_debug("gpio config: %p\n", gpio_pdata);

	chip = devm_kzalloc(&dev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
	chip->dev = &dev->dev;
	chip->reg_base = devm_platform_ioremap_resource(dev, 0);
	if (IS_ERR(chip->reg_base))
		return PTR_ERR(chip->reg_base);

	for (i = 0; i < GSTA_NR_BLOCKS; i++) {
		chip->regs[i] = chip->reg_base + i * 4096;
		/* disable all irqs */
		writel(0, &chip->regs[i]->rimsc);
		writel(0, &chip->regs[i]->fimsc);
		writel(~0, &chip->regs[i]->ic);
	}
	spin_lock_init(&chip->lock);
	gsta_gpio_setup(chip);
	if (gpio_pdata)
		for (i = 0; i < GSTA_NR_GPIO; i++)
			gsta_set_config(chip, i, gpio_pdata->pinconfig[i]);

	/* 384 was used in previous code: be compatible for other drivers */
	err = devm_irq_alloc_descs(&dev->dev, -1, 384,
				   GSTA_NR_GPIO, NUMA_NO_NODE);
	if (err < 0) {
		dev_warn(&dev->dev, "sta2x11 gpio: Can't get irq base (%i)\n",
			 -err);
		return err;
	}
	chip->irq_base = err;

	err = gsta_alloc_irq_chip(chip);
	if (err)
		return err;

	err = devm_request_irq(&dev->dev, pdev->irq, gsta_gpio_handler,
			       IRQF_SHARED, KBUILD_MODNAME, chip);
	if (err < 0) {
		dev_err(&dev->dev, "sta2x11 gpio: Can't request irq (%i)\n",
			-err);
		return err;
	}

	err = devm_gpiochip_add_data(&dev->dev, &chip->gpio, chip);
	if (err < 0) {
		dev_err(&dev->dev, "sta2x11 gpio: Can't register (%i)\n",
			-err);
		return err;
	}

	platform_set_drvdata(dev, chip);
	return 0;
}