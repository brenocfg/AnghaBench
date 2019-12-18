#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  TIMER_WDT_ID ; 
 int /*<<< orphan*/  WDT_DEFAULT_TIME ; 
 int bcm63xx_timer_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm63xx_timer_tick ; 
 int /*<<< orphan*/  bcm63xx_timer_unregister (int /*<<< orphan*/ ) ; 
 TYPE_1__ bcm63xx_wdt_device ; 
 int /*<<< orphan*/  bcm63xx_wdt_isr ; 
 int /*<<< orphan*/  bcm63xx_wdt_miscdev ; 
 scalar_t__ bcm63xx_wdt_settimeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_time ; 

__attribute__((used)) static int bcm63xx_wdt_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *r;

	timer_setup(&bcm63xx_wdt_device.timer, bcm63xx_timer_tick, 0);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "failed to get resources\n");
		return -ENODEV;
	}

	bcm63xx_wdt_device.regs = devm_ioremap_nocache(&pdev->dev, r->start,
							resource_size(r));
	if (!bcm63xx_wdt_device.regs) {
		dev_err(&pdev->dev, "failed to remap I/O resources\n");
		return -ENXIO;
	}

	ret = bcm63xx_timer_register(TIMER_WDT_ID, bcm63xx_wdt_isr, NULL);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register wdt timer isr\n");
		return ret;
	}

	if (bcm63xx_wdt_settimeout(wdt_time)) {
		bcm63xx_wdt_settimeout(WDT_DEFAULT_TIME);
		dev_info(&pdev->dev,
			": wdt_time value must be 1 <= wdt_time <= 256, using %d\n",
			wdt_time);
	}

	ret = misc_register(&bcm63xx_wdt_miscdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register watchdog device\n");
		goto unregister_timer;
	}

	dev_info(&pdev->dev, " started, timer margin: %d sec\n",
						WDT_DEFAULT_TIME);

	return 0;

unregister_timer:
	bcm63xx_timer_unregister(TIMER_WDT_ID);
	return ret;
}