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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct mtk_rtc {int irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  rtc; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mtk_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtk_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rtc_alarmirq ; 
 int /*<<< orphan*/  mtk_rtc_hw_init (struct mtk_rtc*) ; 
 int /*<<< orphan*/  mtk_rtc_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_rtc*) ; 

__attribute__((used)) static int mtk_rtc_probe(struct platform_device *pdev)
{
	struct mtk_rtc *hw;
	struct resource *res;
	int ret;

	hw = devm_kzalloc(&pdev->dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	platform_set_drvdata(pdev, hw);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hw->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hw->base))
		return PTR_ERR(hw->base);

	hw->clk = devm_clk_get(&pdev->dev, "rtc");
	if (IS_ERR(hw->clk)) {
		dev_err(&pdev->dev, "No clock\n");
		return PTR_ERR(hw->clk);
	}

	ret = clk_prepare_enable(hw->clk);
	if (ret)
		return ret;

	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq < 0) {
		ret = hw->irq;
		goto err;
	}

	ret = devm_request_irq(&pdev->dev, hw->irq, mtk_rtc_alarmirq,
			       0, dev_name(&pdev->dev), hw);
	if (ret) {
		dev_err(&pdev->dev, "Can't request IRQ\n");
		goto err;
	}

	mtk_rtc_hw_init(hw);

	device_init_wakeup(&pdev->dev, true);

	hw->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					   &mtk_rtc_ops, THIS_MODULE);
	if (IS_ERR(hw->rtc)) {
		ret = PTR_ERR(hw->rtc);
		dev_err(&pdev->dev, "Unable to register device\n");
		goto err;
	}

	return 0;
err:
	clk_disable_unprepare(hw->clk);

	return ret;
}