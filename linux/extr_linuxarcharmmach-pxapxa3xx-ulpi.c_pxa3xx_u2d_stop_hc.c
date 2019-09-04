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
struct usb_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_pxa310 () ; 
 int /*<<< orphan*/  pxa310_stop_otg_hc () ; 
 TYPE_1__* u2d ; 

void pxa3xx_u2d_stop_hc(struct usb_bus *host)
{
	/* In case the PXA3xx ULPI isn't used, do nothing. */
	if (!u2d)
		return;

	if (cpu_is_pxa310())
		pxa310_stop_otg_hc();

	clk_disable_unprepare(u2d->clk);
}