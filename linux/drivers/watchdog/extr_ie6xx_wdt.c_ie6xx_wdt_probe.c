#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ sch_wdtba; int /*<<< orphan*/  unlock_sequence; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ WDTLR ; 
 int WDT_LOCK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_4__ ie6xx_wdt_data ; 
 int /*<<< orphan*/  ie6xx_wdt_debugfs_exit () ; 
 int /*<<< orphan*/  ie6xx_wdt_debugfs_init () ; 
 TYPE_1__ ie6xx_wdt_dev ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ie6xx_wdt_probe(struct platform_device *pdev)
{
	struct resource *res;
	u8 wdtlr;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res)
		return -ENODEV;

	if (!request_region(res->start, resource_size(res), pdev->name)) {
		dev_err(&pdev->dev, "Watchdog region 0x%llx already in use!\n",
			(u64)res->start);
		return -EBUSY;
	}

	ie6xx_wdt_data.sch_wdtba = res->start;
	dev_dbg(&pdev->dev, "WDT = 0x%X\n", ie6xx_wdt_data.sch_wdtba);

	ie6xx_wdt_dev.timeout = timeout;
	watchdog_set_nowayout(&ie6xx_wdt_dev, nowayout);
	ie6xx_wdt_dev.parent = &pdev->dev;

	spin_lock_init(&ie6xx_wdt_data.unlock_sequence);

	wdtlr = inb(ie6xx_wdt_data.sch_wdtba + WDTLR);
	if (wdtlr & WDT_LOCK)
		dev_warn(&pdev->dev,
			"Watchdog Timer is Locked (Reg=0x%x)\n", wdtlr);

	ie6xx_wdt_debugfs_init();

	ret = watchdog_register_device(&ie6xx_wdt_dev);
	if (ret)
		goto misc_register_error;

	return 0;

misc_register_error:
	ie6xx_wdt_debugfs_exit();
	release_region(res->start, resource_size(res));
	ie6xx_wdt_data.sch_wdtba = 0;
	return ret;
}