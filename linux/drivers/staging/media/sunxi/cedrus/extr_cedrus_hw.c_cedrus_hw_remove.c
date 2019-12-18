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
struct cedrus_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ahb_clk; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  ram_clk; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_sram_release (int /*<<< orphan*/ ) ; 

void cedrus_hw_remove(struct cedrus_dev *dev)
{
	reset_control_assert(dev->rstc);

	clk_disable_unprepare(dev->ram_clk);
	clk_disable_unprepare(dev->mod_clk);
	clk_disable_unprepare(dev->ahb_clk);

	sunxi_sram_release(dev->dev);

	of_reserved_mem_device_release(dev->dev);
}