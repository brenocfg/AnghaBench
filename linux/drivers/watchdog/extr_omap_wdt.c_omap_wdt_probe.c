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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  bootstatus; int /*<<< orphan*/ * parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct omap_wdt_dev {int omap_wdt_users; int wdt_trgr_pattern; int /*<<< orphan*/ * dev; TYPE_1__ wdog; scalar_t__ base; int /*<<< orphan*/  lock; } ;
struct omap_wd_timer_platform_data {int (* read_reset_sources ) () ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int OMAP_MPU_WD_RST_SRC_ID_SHIFT ; 
 scalar_t__ OMAP_WATCHDOG_REV ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  TIMER_MARGIN_DEFAULT ; 
 int /*<<< orphan*/  TIMER_MARGIN_MAX ; 
 int /*<<< orphan*/  TIMER_MARGIN_MIN ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 struct omap_wd_timer_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct omap_wdt_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ early_enable ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  omap_wdt_disable (struct omap_wdt_dev*) ; 
 int /*<<< orphan*/  omap_wdt_info ; 
 int /*<<< orphan*/  omap_wdt_ops ; 
 int /*<<< orphan*/  omap_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_wdt_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int stub1 () ; 
 int /*<<< orphan*/  timer_margin ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_wdt_probe(struct platform_device *pdev)
{
	struct omap_wd_timer_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct omap_wdt_dev *wdev;
	int ret;

	wdev = devm_kzalloc(&pdev->dev, sizeof(*wdev), GFP_KERNEL);
	if (!wdev)
		return -ENOMEM;

	wdev->omap_wdt_users	= false;
	wdev->dev		= &pdev->dev;
	wdev->wdt_trgr_pattern	= 0x1234;
	mutex_init(&wdev->lock);

	/* reserve static register mappings */
	wdev->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdev->base))
		return PTR_ERR(wdev->base);

	wdev->wdog.info = &omap_wdt_info;
	wdev->wdog.ops = &omap_wdt_ops;
	wdev->wdog.min_timeout = TIMER_MARGIN_MIN;
	wdev->wdog.max_timeout = TIMER_MARGIN_MAX;
	wdev->wdog.timeout = TIMER_MARGIN_DEFAULT;
	wdev->wdog.parent = &pdev->dev;

	watchdog_init_timeout(&wdev->wdog, timer_margin, &pdev->dev);

	watchdog_set_nowayout(&wdev->wdog, nowayout);

	platform_set_drvdata(pdev, wdev);

	pm_runtime_enable(wdev->dev);
	pm_runtime_get_sync(wdev->dev);

	if (pdata && pdata->read_reset_sources) {
		u32 rs = pdata->read_reset_sources();
		if (rs & (1 << OMAP_MPU_WD_RST_SRC_ID_SHIFT))
			wdev->wdog.bootstatus = WDIOF_CARDRESET;
	}

	if (!early_enable)
		omap_wdt_disable(wdev);

	ret = watchdog_register_device(&wdev->wdog);
	if (ret) {
		pm_runtime_disable(wdev->dev);
		return ret;
	}

	pr_info("OMAP Watchdog Timer Rev 0x%02x: initial timeout %d sec\n",
		readl_relaxed(wdev->base + OMAP_WATCHDOG_REV) & 0xFF,
		wdev->wdog.timeout);

	if (early_enable)
		omap_wdt_start(&wdev->wdog);

	pm_runtime_put(wdev->dev);

	return 0;
}