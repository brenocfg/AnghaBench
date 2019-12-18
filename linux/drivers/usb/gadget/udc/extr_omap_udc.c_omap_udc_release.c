#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ done; scalar_t__ dc_clk; scalar_t__ hhc_clk; scalar_t__ clk_requested; int /*<<< orphan*/ * transceiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UDC_SYSCON1 ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  omap_udc_enable_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pullup_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_proc_file () ; 
 TYPE_1__* udc ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_udc_release(struct device *dev)
{
	pullup_disable(udc);
	if (!IS_ERR_OR_NULL(udc->transceiver)) {
		usb_put_phy(udc->transceiver);
		udc->transceiver = NULL;
	}
	omap_writew(0, UDC_SYSCON1);
	remove_proc_file();
	if (udc->dc_clk) {
		if (udc->clk_requested)
			omap_udc_enable_clock(0);
		clk_put(udc->hhc_clk);
		clk_put(udc->dc_clk);
	}
	if (udc->done)
		complete(udc->done);
	kfree(udc);
}