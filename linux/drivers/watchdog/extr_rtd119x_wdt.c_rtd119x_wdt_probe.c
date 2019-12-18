#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int timeout; int max_timeout; int min_timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct rtd119x_watchdog_device {TYPE_1__ wdt_dev; scalar_t__ base; scalar_t__ clk; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ RTD119X_TCWTR ; 
 int /*<<< orphan*/  RTD119X_TCWTR_WDCLR ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct rtd119x_watchdog_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtd119x_watchdog_device*) ; 
 int /*<<< orphan*/  rtd119x_clk_disable_unprepare ; 
 int /*<<< orphan*/  rtd119x_wdt_info ; 
 int /*<<< orphan*/  rtd119x_wdt_ops ; 
 int /*<<< orphan*/  rtd119x_wdt_set_timeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rtd119x_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct rtd119x_watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd119x_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtd119x_watchdog_device *data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret)
		return ret;
	ret = devm_add_action_or_reset(dev, rtd119x_clk_disable_unprepare,
				       data->clk);
	if (ret)
		return ret;

	data->wdt_dev.info = &rtd119x_wdt_info;
	data->wdt_dev.ops = &rtd119x_wdt_ops;
	data->wdt_dev.timeout = 120;
	data->wdt_dev.max_timeout = 0xffffffff / clk_get_rate(data->clk);
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.parent = dev;

	watchdog_stop_on_reboot(&data->wdt_dev);
	watchdog_set_drvdata(&data->wdt_dev, data);
	platform_set_drvdata(pdev, data);

	writel_relaxed(RTD119X_TCWTR_WDCLR, data->base + RTD119X_TCWTR);
	rtd119x_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);
	rtd119x_wdt_stop(&data->wdt_dev);

	return devm_watchdog_register_device(dev, &data->wdt_dev);
}