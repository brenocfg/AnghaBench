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
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_4__ {int pretimeout; int min_timeout; int max_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  bootstatus; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct qcom_wdt {int rate; TYPE_1__ wdd; scalar_t__ const* layout; struct clk* base; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDT_STS ; 
 int clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct clk*) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  min (int,unsigned int) ; 
 scalar_t__* of_device_get_match_data (struct device*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_wdt*) ; 
 int /*<<< orphan*/  qcom_clk_disable_unprepare ; 
 int /*<<< orphan*/  qcom_wdt_info ; 
 int /*<<< orphan*/  qcom_wdt_isr ; 
 int /*<<< orphan*/  qcom_wdt_ops ; 
 int /*<<< orphan*/  qcom_wdt_pt_info ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  wdt_addr (struct qcom_wdt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct qcom_wdt *wdt;
	struct resource *res;
	struct device_node *np = dev->of_node;
	const u32 *regs;
	u32 percpu_offset;
	int irq, ret;
	struct clk *clk;

	regs = of_device_get_match_data(dev);
	if (!regs) {
		dev_err(dev, "Unsupported QCOM WDT module\n");
		return -ENODEV;
	}

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENOMEM;

	/* We use CPU0's DGT for the watchdog */
	if (of_property_read_u32(np, "cpu-offset", &percpu_offset))
		percpu_offset = 0;

	res->start += percpu_offset;
	res->end += percpu_offset;

	wdt->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	clk = devm_clk_get(dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(dev, "failed to get input clock\n");
		return PTR_ERR(clk);
	}

	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(dev, "failed to setup clock\n");
		return ret;
	}
	ret = devm_add_action_or_reset(dev, qcom_clk_disable_unprepare, clk);
	if (ret)
		return ret;

	/*
	 * We use the clock rate to calculate the max timeout, so ensure it's
	 * not zero to avoid a divide-by-zero exception.
	 *
	 * WATCHDOG_CORE assumes units of seconds, if the WDT is clocked such
	 * that it would bite before a second elapses it's usefulness is
	 * limited.  Bail if this is the case.
	 */
	wdt->rate = clk_get_rate(clk);
	if (wdt->rate == 0 ||
	    wdt->rate > 0x10000000U) {
		dev_err(dev, "invalid clock rate\n");
		return -EINVAL;
	}

	/* check if there is pretimeout support */
	irq = platform_get_irq(pdev, 0);
	if (irq > 0) {
		ret = devm_request_irq(dev, irq, qcom_wdt_isr,
				       IRQF_TRIGGER_RISING,
				       "wdt_bark", &wdt->wdd);
		if (ret)
			return ret;

		wdt->wdd.info = &qcom_wdt_pt_info;
		wdt->wdd.pretimeout = 1;
	} else {
		if (irq == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		wdt->wdd.info = &qcom_wdt_info;
	}

	wdt->wdd.ops = &qcom_wdt_ops;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 0x10000000U / wdt->rate;
	wdt->wdd.parent = dev;
	wdt->layout = regs;

	if (readl(wdt_addr(wdt, WDT_STS)) & 1)
		wdt->wdd.bootstatus = WDIOF_CARDRESET;

	/*
	 * If 'timeout-sec' unspecified in devicetree, assume a 30 second
	 * default, unless the max timeout is less than 30 seconds, then use
	 * the max instead.
	 */
	wdt->wdd.timeout = min(wdt->wdd.max_timeout, 30U);
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	ret = devm_watchdog_register_device(dev, &wdt->wdd);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, wdt);
	return 0;
}