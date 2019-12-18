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
struct omap_usb {int /*<<< orphan*/  optclk; int /*<<< orphan*/  wkupclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_usb2_disable_clocks(struct omap_usb *phy)
{
	clk_disable_unprepare(phy->wkupclk);
	if (!IS_ERR(phy->optclk))
		clk_disable_unprepare(phy->optclk);

	return 0;
}