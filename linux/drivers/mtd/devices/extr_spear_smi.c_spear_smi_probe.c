#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct spear_smi_plat_data {scalar_t__ clk_rate; int num_flashes; int /*<<< orphan*/ * np; } ;
struct spear_smi {scalar_t__ clk_rate; int num_flashes; int /*<<< orphan*/  clk; struct platform_device* pdev; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_base; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {struct spear_smi_plat_data* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_NUM_FLASH_CHIP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SMI_MAX_CLOCK_FREQ ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct spear_smi_plat_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spear_smi*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spear_smi*) ; 
 int /*<<< orphan*/  spear_smi_hw_init (struct spear_smi*) ; 
 int /*<<< orphan*/  spear_smi_int_handler ; 
 int spear_smi_probe_config_dt (struct platform_device*,struct device_node*) ; 
 int spear_smi_setup_banks (struct platform_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear_smi_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct spear_smi_plat_data *pdata = NULL;
	struct spear_smi *dev;
	struct resource *smi_base;
	int irq, ret = 0;
	int i;

	if (np) {
		pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata) {
			ret = -ENOMEM;
			goto err;
		}
		pdev->dev.platform_data = pdata;
		ret = spear_smi_probe_config_dt(pdev, np);
		if (ret) {
			ret = -ENODEV;
			dev_err(&pdev->dev, "no platform data\n");
			goto err;
		}
	} else {
		pdata = dev_get_platdata(&pdev->dev);
		if (!pdata) {
			ret = -ENODEV;
			dev_err(&pdev->dev, "no platform data\n");
			goto err;
		}
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = -ENODEV;
		dev_err(&pdev->dev, "invalid smi irq\n");
		goto err;
	}

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_ATOMIC);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	smi_base = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	dev->io_base = devm_ioremap_resource(&pdev->dev, smi_base);
	if (IS_ERR(dev->io_base)) {
		ret = PTR_ERR(dev->io_base);
		goto err;
	}

	dev->pdev = pdev;
	dev->clk_rate = pdata->clk_rate;

	if (dev->clk_rate > SMI_MAX_CLOCK_FREQ)
		dev->clk_rate = SMI_MAX_CLOCK_FREQ;

	dev->num_flashes = pdata->num_flashes;

	if (dev->num_flashes > MAX_NUM_FLASH_CHIP) {
		dev_err(&pdev->dev, "exceeding max number of flashes\n");
		dev->num_flashes = MAX_NUM_FLASH_CHIP;
	}

	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		ret = PTR_ERR(dev->clk);
		goto err;
	}

	ret = clk_prepare_enable(dev->clk);
	if (ret)
		goto err;

	ret = devm_request_irq(&pdev->dev, irq, spear_smi_int_handler, 0,
			       pdev->name, dev);
	if (ret) {
		dev_err(&dev->pdev->dev, "SMI IRQ allocation failed\n");
		goto err_irq;
	}

	mutex_init(&dev->lock);
	init_waitqueue_head(&dev->cmd_complete);
	spear_smi_hw_init(dev);
	platform_set_drvdata(pdev, dev);

	/* loop for each serial nor-flash which is connected to smi */
	for (i = 0; i < dev->num_flashes; i++) {
		ret = spear_smi_setup_banks(pdev, i, pdata->np[i]);
		if (ret) {
			dev_err(&dev->pdev->dev, "bank setup failed\n");
			goto err_irq;
		}
	}

	return 0;

err_irq:
	clk_disable_unprepare(dev->clk);
err:
	return ret;
}