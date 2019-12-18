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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; int /*<<< orphan*/  timer; int /*<<< orphan*/  inuse; scalar_t__ queue; int /*<<< orphan*/  stop; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 TYPE_1__ mtx1_wdt_device ; 
 int /*<<< orphan*/  mtx1_wdt_misc ; 
 int /*<<< orphan*/  mtx1_wdt_start () ; 
 int /*<<< orphan*/  mtx1_wdt_trigger ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtx1_wdt_probe(struct platform_device *pdev)
{
	int ret;

	mtx1_wdt_device.gpiod = devm_gpiod_get(&pdev->dev,
					       NULL, GPIOD_OUT_HIGH);
	if (IS_ERR(mtx1_wdt_device.gpiod)) {
		dev_err(&pdev->dev, "failed to request gpio");
		return PTR_ERR(mtx1_wdt_device.gpiod);
	}

	spin_lock_init(&mtx1_wdt_device.lock);
	init_completion(&mtx1_wdt_device.stop);
	mtx1_wdt_device.queue = 0;
	clear_bit(0, &mtx1_wdt_device.inuse);
	timer_setup(&mtx1_wdt_device.timer, mtx1_wdt_trigger, 0);
	mtx1_wdt_device.default_ticks = ticks;

	ret = misc_register(&mtx1_wdt_misc);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register\n");
		return ret;
	}
	mtx1_wdt_start();
	dev_info(&pdev->dev, "MTX-1 Watchdog driver\n");
	return 0;
}