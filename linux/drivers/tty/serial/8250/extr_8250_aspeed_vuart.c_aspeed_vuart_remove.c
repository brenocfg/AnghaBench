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
struct platform_device {int dummy; } ;
struct aspeed_vuart {int /*<<< orphan*/  clk; TYPE_1__* dev; int /*<<< orphan*/  line; int /*<<< orphan*/  unthrottle_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_vuart_attr_group ; 
 int /*<<< orphan*/  aspeed_vuart_set_enabled (struct aspeed_vuart*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct aspeed_vuart* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_vuart_remove(struct platform_device *pdev)
{
	struct aspeed_vuart *vuart = platform_get_drvdata(pdev);

	del_timer_sync(&vuart->unthrottle_timer);
	aspeed_vuart_set_enabled(vuart, false);
	serial8250_unregister_port(vuart->line);
	sysfs_remove_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	clk_disable_unprepare(vuart->clk);

	return 0;
}