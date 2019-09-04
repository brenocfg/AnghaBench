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
struct bcm_device {int clk_enabled; int (* set_shutdown ) (struct bcm_device*,int) ;int (* set_device_wakeup ) (struct bcm_device*,int) ;int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int stub1 (struct bcm_device*,int) ; 
 int stub2 (struct bcm_device*,int) ; 
 int stub3 (struct bcm_device*,int) ; 

__attribute__((used)) static int bcm_gpio_set_power(struct bcm_device *dev, bool powered)
{
	int err;

	if (powered && !IS_ERR(dev->clk) && !dev->clk_enabled) {
		err = clk_prepare_enable(dev->clk);
		if (err)
			return err;
	}

	err = dev->set_shutdown(dev, powered);
	if (err)
		goto err_clk_disable;

	err = dev->set_device_wakeup(dev, powered);
	if (err)
		goto err_revert_shutdown;

	if (!powered && !IS_ERR(dev->clk) && dev->clk_enabled)
		clk_disable_unprepare(dev->clk);

	dev->clk_enabled = powered;

	return 0;

err_revert_shutdown:
	dev->set_shutdown(dev, !powered);
err_clk_disable:
	if (powered && !IS_ERR(dev->clk) && !dev->clk_enabled)
		clk_disable_unprepare(dev->clk);
	return err;
}