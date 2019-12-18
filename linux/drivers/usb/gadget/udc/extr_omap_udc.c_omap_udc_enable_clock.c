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
struct TYPE_2__ {int /*<<< orphan*/ * dc_clk; int /*<<< orphan*/ * hhc_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ *) ; 
 TYPE_1__* udc ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void omap_udc_enable_clock(int enable)
{
	if (udc == NULL || udc->dc_clk == NULL || udc->hhc_clk == NULL)
		return;

	if (enable) {
		clk_enable(udc->dc_clk);
		clk_enable(udc->hhc_clk);
		udelay(100);
	} else {
		clk_disable(udc->hhc_clk);
		clk_disable(udc->dc_clk);
	}
}