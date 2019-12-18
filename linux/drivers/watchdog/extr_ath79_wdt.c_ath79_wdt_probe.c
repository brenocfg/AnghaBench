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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int WDOG_CTRL_LAST_RESET ; 
 int /*<<< orphan*/  WDOG_REG_CTRL ; 
 int /*<<< orphan*/  ath79_wdt_miscdev ; 
 int ath79_wdt_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_status ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int max_timeout ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int timeout ; 
 scalar_t__ wdt_base ; 
 scalar_t__ wdt_clk ; 
 int wdt_freq ; 

__attribute__((used)) static int ath79_wdt_probe(struct platform_device *pdev)
{
	u32 ctrl;
	int err;

	if (wdt_base)
		return -EBUSY;

	wdt_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt_base))
		return PTR_ERR(wdt_base);

	wdt_clk = devm_clk_get(&pdev->dev, "wdt");
	if (IS_ERR(wdt_clk))
		return PTR_ERR(wdt_clk);

	err = clk_prepare_enable(wdt_clk);
	if (err)
		return err;

	wdt_freq = clk_get_rate(wdt_clk);
	if (!wdt_freq) {
		err = -EINVAL;
		goto err_clk_disable;
	}

	max_timeout = (0xfffffffful / wdt_freq);
	if (timeout < 1 || timeout > max_timeout) {
		timeout = max_timeout;
		dev_info(&pdev->dev,
			"timeout value must be 0 < timeout < %d, using %d\n",
			max_timeout, timeout);
	}

	ctrl = ath79_wdt_rr(WDOG_REG_CTRL);
	boot_status = (ctrl & WDOG_CTRL_LAST_RESET) ? WDIOF_CARDRESET : 0;

	err = misc_register(&ath79_wdt_miscdev);
	if (err) {
		dev_err(&pdev->dev,
			"unable to register misc device, err=%d\n", err);
		goto err_clk_disable;
	}

	return 0;

err_clk_disable:
	clk_disable_unprepare(wdt_clk);
	return err;
}