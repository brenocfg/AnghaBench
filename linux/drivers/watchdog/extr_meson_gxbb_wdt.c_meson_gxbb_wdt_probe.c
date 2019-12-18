#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int min_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_hw_heartbeat_ms; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct meson_gxbb_wdt {TYPE_1__ wdt_dev; scalar_t__ reg_base; scalar_t__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GXBB_WDT_CTRL_CLKDIV_EN ; 
 int GXBB_WDT_CTRL_CLK_EN ; 
 int GXBB_WDT_CTRL_DIV_MASK ; 
 int GXBB_WDT_CTRL_EE_RESET ; 
 scalar_t__ GXBB_WDT_CTRL_REG ; 
 int /*<<< orphan*/  GXBB_WDT_TCNT_SETUP_MASK ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct meson_gxbb_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  meson_clk_disable_unprepare ; 
 int /*<<< orphan*/  meson_gxbb_wdt_info ; 
 int /*<<< orphan*/  meson_gxbb_wdt_ops ; 
 int /*<<< orphan*/  meson_gxbb_wdt_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_gxbb_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct meson_gxbb_wdt*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int meson_gxbb_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct meson_gxbb_wdt *data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->reg_base))
		return PTR_ERR(data->reg_base);

	data->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret)
		return ret;
	ret = devm_add_action_or_reset(dev, meson_clk_disable_unprepare,
				       data->clk);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, data);

	data->wdt_dev.parent = dev;
	data->wdt_dev.info = &meson_gxbb_wdt_info;
	data->wdt_dev.ops = &meson_gxbb_wdt_ops;
	data->wdt_dev.max_hw_heartbeat_ms = GXBB_WDT_TCNT_SETUP_MASK;
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.timeout = DEFAULT_TIMEOUT;
	watchdog_set_drvdata(&data->wdt_dev, data);

	/* Setup with 1ms timebase */
	writel(((clk_get_rate(data->clk) / 1000) & GXBB_WDT_CTRL_DIV_MASK) |
		GXBB_WDT_CTRL_EE_RESET |
		GXBB_WDT_CTRL_CLK_EN |
		GXBB_WDT_CTRL_CLKDIV_EN,
		data->reg_base + GXBB_WDT_CTRL_REG);

	meson_gxbb_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);

	watchdog_stop_on_reboot(&data->wdt_dev);
	return devm_watchdog_register_device(dev, &data->wdt_dev);
}