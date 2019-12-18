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
typedef  int u32 ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct asm9260_rtc_priv {int /*<<< orphan*/  clk; scalar_t__ rtc; scalar_t__ iobase; struct device* dev; } ;

/* Variables and functions */
 int BM_AMR_OFF ; 
 int BM_CLKEN ; 
 int BM_CTCRST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HW_AMR ; 
 scalar_t__ HW_CCR ; 
 scalar_t__ HW_CIIR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  asm9260_rtc_irq ; 
 int /*<<< orphan*/  asm9260_rtc_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct asm9260_rtc_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct asm9260_rtc_priv*) ; 
 scalar_t__ devm_rtc_device_register (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct asm9260_rtc_priv*) ; 

__attribute__((used)) static int asm9260_rtc_probe(struct platform_device *pdev)
{
	struct asm9260_rtc_priv *priv;
	struct device *dev = &pdev->dev;
	struct resource	*res;
	int irq_alarm, ret;
	u32 ccr;

	priv = devm_kzalloc(dev, sizeof(struct asm9260_rtc_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = &pdev->dev;
	platform_set_drvdata(pdev, priv);

	irq_alarm = platform_get_irq(pdev, 0);
	if (irq_alarm < 0)
		return irq_alarm;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->iobase = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->iobase))
		return PTR_ERR(priv->iobase);

	priv->clk = devm_clk_get(dev, "ahb");
	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(dev, "Failed to enable clk!\n");
		return ret;
	}

	ccr = ioread32(priv->iobase + HW_CCR);
	/* if dev is not enabled, reset it */
	if ((ccr & (BM_CLKEN | BM_CTCRST)) != BM_CLKEN) {
		iowrite32(BM_CTCRST, priv->iobase + HW_CCR);
		ccr = 0;
	}

	iowrite32(BM_CLKEN | ccr, priv->iobase + HW_CCR);
	iowrite32(0, priv->iobase + HW_CIIR);
	iowrite32(BM_AMR_OFF, priv->iobase + HW_AMR);

	priv->rtc = devm_rtc_device_register(dev, dev_name(dev),
					     &asm9260_rtc_ops, THIS_MODULE);
	if (IS_ERR(priv->rtc)) {
		ret = PTR_ERR(priv->rtc);
		dev_err(dev, "Failed to register RTC device: %d\n", ret);
		goto err_return;
	}

	ret = devm_request_threaded_irq(dev, irq_alarm, NULL,
					asm9260_rtc_irq, IRQF_ONESHOT,
					dev_name(dev), priv);
	if (ret < 0) {
		dev_err(dev, "can't get irq %i, err %d\n",
			irq_alarm, ret);
		goto err_return;
	}

	return 0;

err_return:
	clk_disable_unprepare(priv->clk);
	return ret;
}