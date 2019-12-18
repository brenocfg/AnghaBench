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
struct intel_lpss {int /*<<< orphan*/  clk; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lpss_unregister_clock_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_lpss_unregister_clock(struct intel_lpss *lpss)
{
	if (IS_ERR_OR_NULL(lpss->clk))
		return;

	clkdev_drop(lpss->clock);
	intel_lpss_unregister_clock_tree(lpss->clk);
}