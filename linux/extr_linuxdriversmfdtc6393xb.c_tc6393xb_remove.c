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
struct tc6393xb_platform_data {int (* disable ) (struct platform_device*) ;int /*<<< orphan*/  (* teardown ) (struct platform_device*) ;} ;
struct TYPE_2__ {int base; } ;
struct tc6393xb {int /*<<< orphan*/  clk; int /*<<< orphan*/  rscr; int /*<<< orphan*/  scr; TYPE_1__ gpio; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct tc6393xb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc6393xb*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct tc6393xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int stub2 (struct platform_device*) ; 
 int /*<<< orphan*/  tc6393xb_detach_irq (struct platform_device*) ; 

__attribute__((used)) static int tc6393xb_remove(struct platform_device *dev)
{
	struct tc6393xb_platform_data *tcpd = dev_get_platdata(&dev->dev);
	struct tc6393xb *tc6393xb = platform_get_drvdata(dev);
	int ret;

	mfd_remove_devices(&dev->dev);

	if (tcpd->teardown)
		tcpd->teardown(dev);

	tc6393xb_detach_irq(dev);

	if (tc6393xb->gpio.base != -1)
		gpiochip_remove(&tc6393xb->gpio);

	ret = tcpd->disable(dev);
	clk_disable_unprepare(tc6393xb->clk);
	iounmap(tc6393xb->scr);
	release_resource(&tc6393xb->rscr);
	clk_put(tc6393xb->clk);
	kfree(tc6393xb);

	return ret;
}