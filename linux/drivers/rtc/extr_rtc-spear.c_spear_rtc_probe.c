#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct spear_rtc_config {TYPE_1__* clk; TYPE_1__* rtc; int /*<<< orphan*/  lock; TYPE_1__* ioaddr; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int uie_unsupported; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (TYPE_1__*) ; 
 int clk_prepare_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct spear_rtc_config* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spear_rtc_config*) ; 
 TYPE_1__* devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spear_rtc_irq ; 
 int /*<<< orphan*/  spear_rtc_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spear_rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct spear_rtc_config *config;
	int status = 0;
	int irq;

	config = devm_kzalloc(&pdev->dev, sizeof(*config), GFP_KERNEL);
	if (!config)
		return -ENOMEM;

	/* alarm irqs */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	status = devm_request_irq(&pdev->dev, irq, spear_rtc_irq, 0, pdev->name,
			config);
	if (status) {
		dev_err(&pdev->dev, "Alarm interrupt IRQ%d already claimed\n",
				irq);
		return status;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	config->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(config->ioaddr))
		return PTR_ERR(config->ioaddr);

	config->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(config->clk))
		return PTR_ERR(config->clk);

	status = clk_prepare_enable(config->clk);
	if (status < 0)
		return status;

	spin_lock_init(&config->lock);
	platform_set_drvdata(pdev, config);

	config->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					&spear_rtc_ops, THIS_MODULE);
	if (IS_ERR(config->rtc)) {
		dev_err(&pdev->dev, "can't register RTC device, err %ld\n",
				PTR_ERR(config->rtc));
		status = PTR_ERR(config->rtc);
		goto err_disable_clock;
	}

	config->rtc->uie_unsupported = 1;

	if (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	return 0;

err_disable_clock:
	clk_disable_unprepare(config->clk);

	return status;
}