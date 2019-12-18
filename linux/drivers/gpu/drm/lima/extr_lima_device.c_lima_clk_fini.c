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
struct lima_device {int /*<<< orphan*/  clk_bus; int /*<<< orphan*/  clk_gpu; int /*<<< orphan*/ * reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lima_clk_fini(struct lima_device *dev)
{
	if (dev->reset != NULL)
		reset_control_assert(dev->reset);
	clk_disable_unprepare(dev->clk_gpu);
	clk_disable_unprepare(dev->clk_bus);
}