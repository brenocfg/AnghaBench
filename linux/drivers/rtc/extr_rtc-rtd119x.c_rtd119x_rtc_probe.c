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
typedef  int u32 ;
struct rtd119x_rtc {int base_year; scalar_t__ rtcdev; scalar_t__ clk; scalar_t__ base; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ RTD_RTCACR ; 
 int RTD_RTCACR_RTCPWR ; 
 scalar_t__ RTD_RTCDATE1 ; 
 scalar_t__ RTD_RTCDATE2 ; 
 scalar_t__ RTD_RTCHR ; 
 scalar_t__ RTD_RTCMIN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct rtd119x_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ of_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtd119x_rtc*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rtd119x_rtc_ops ; 
 int /*<<< orphan*/  rtd119x_rtc_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  rtd119x_rtc_set_enabled (TYPE_1__*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int rtd119x_rtc_probe(struct platform_device *pdev)
{
	struct rtd119x_rtc *data;
	struct resource *res;
	u32 val;
	int ret;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);
	data->base_year = 2014;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->clk = of_clk_get(pdev->dev.of_node, 0);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret) {
		clk_put(data->clk);
		return ret;
	}

	val = readl_relaxed(data->base + RTD_RTCACR);
	if (!(val & RTD_RTCACR_RTCPWR)) {
		writel_relaxed(RTD_RTCACR_RTCPWR, data->base + RTD_RTCACR);

		rtd119x_rtc_reset(&pdev->dev);

		writel_relaxed(0, data->base + RTD_RTCMIN);
		writel_relaxed(0, data->base + RTD_RTCHR);
		writel_relaxed(0, data->base + RTD_RTCDATE1);
		writel_relaxed(0, data->base + RTD_RTCDATE2);
	}

	rtd119x_rtc_set_enabled(&pdev->dev, true);

	data->rtcdev = devm_rtc_device_register(&pdev->dev, "rtc",
						&rtd119x_rtc_ops, THIS_MODULE);
	if (IS_ERR(data->rtcdev)) {
		dev_err(&pdev->dev, "failed to register rtc device");
		clk_disable_unprepare(data->clk);
		clk_put(data->clk);
		return PTR_ERR(data->rtcdev);
	}

	return 0;
}