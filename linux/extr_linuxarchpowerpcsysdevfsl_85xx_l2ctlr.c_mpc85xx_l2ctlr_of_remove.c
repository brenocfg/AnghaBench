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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2ctlr ; 
 int /*<<< orphan*/  remove_cache_sram (struct platform_device*) ; 

__attribute__((used)) static int mpc85xx_l2ctlr_of_remove(struct platform_device *dev)
{
	BUG_ON(!l2ctlr);

	iounmap(l2ctlr);
	remove_cache_sram(dev);
	dev_info(&dev->dev, "MPC85xx L2 controller unloaded\n");

	return 0;
}