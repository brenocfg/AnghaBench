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
struct ssc_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  regs; int /*<<< orphan*/  list; int /*<<< orphan*/  clk; int /*<<< orphan*/  phybase; int /*<<< orphan*/  clk_from_rk_pin; struct atmel_ssc_platform_data* pdata; struct platform_device* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct atmel_ssc_platform_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR ; 
 struct atmel_ssc_platform_data* atmel_ssc_get_driver_data (struct platform_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct ssc_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ssc_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssc_list ; 
 int /*<<< orphan*/  ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssc_sound_dai_probe (struct ssc_device*) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  user_lock ; 

__attribute__((used)) static int ssc_probe(struct platform_device *pdev)
{
	struct resource *regs;
	struct ssc_device *ssc;
	const struct atmel_ssc_platform_data *plat_dat;

	ssc = devm_kzalloc(&pdev->dev, sizeof(struct ssc_device), GFP_KERNEL);
	if (!ssc) {
		dev_dbg(&pdev->dev, "out of memory\n");
		return -ENOMEM;
	}

	ssc->pdev = pdev;

	plat_dat = atmel_ssc_get_driver_data(pdev);
	if (!plat_dat)
		return -ENODEV;
	ssc->pdata = (struct atmel_ssc_platform_data *)plat_dat;

	if (pdev->dev.of_node) {
		struct device_node *np = pdev->dev.of_node;
		ssc->clk_from_rk_pin =
			of_property_read_bool(np, "atmel,clk-from-rk-pin");
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ssc->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(ssc->regs))
		return PTR_ERR(ssc->regs);

	ssc->phybase = regs->start;

	ssc->clk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(ssc->clk)) {
		dev_dbg(&pdev->dev, "no pclk clock defined\n");
		return -ENXIO;
	}

	/* disable all interrupts */
	clk_prepare_enable(ssc->clk);
	ssc_writel(ssc->regs, IDR, -1);
	ssc_readl(ssc->regs, SR);
	clk_disable_unprepare(ssc->clk);

	ssc->irq = platform_get_irq(pdev, 0);
	if (!ssc->irq) {
		dev_dbg(&pdev->dev, "could not get irq\n");
		return -ENXIO;
	}

	spin_lock(&user_lock);
	list_add_tail(&ssc->list, &ssc_list);
	spin_unlock(&user_lock);

	platform_set_drvdata(pdev, ssc);

	dev_info(&pdev->dev, "Atmel SSC device at 0x%p (irq %d)\n",
			ssc->regs, ssc->irq);

	if (ssc_sound_dai_probe(ssc))
		dev_err(&pdev->dev, "failed to auto-setup ssc for audio\n");

	return 0;
}