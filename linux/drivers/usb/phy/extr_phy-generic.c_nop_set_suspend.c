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
struct usb_phy_generic {int /*<<< orphan*/  clk; } ;
struct usb_phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct usb_phy_generic* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nop_set_suspend(struct usb_phy *x, int suspend)
{
	struct usb_phy_generic *nop = dev_get_drvdata(x->dev);

	if (!IS_ERR(nop->clk)) {
		if (suspend)
			clk_disable_unprepare(nop->clk);
		else
			clk_prepare_enable(nop->clk);
	}

	return 0;
}