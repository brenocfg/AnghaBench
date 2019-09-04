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
struct usbtll_omap {int nch; int /*<<< orphan*/ * ch_clk; } ;
struct usbhs_omap_platform_data {int /*<<< orphan*/ * port_mode; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct usbtll_omap* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ omap_usb_mode_needs_tll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tll_dev ; 
 int /*<<< orphan*/  tll_lock ; 

int omap_tll_enable(struct usbhs_omap_platform_data *pdata)
{
	int i;
	struct usbtll_omap *tll;

	if (!tll_dev)
		return -ENODEV;

	pm_runtime_get_sync(tll_dev);

	spin_lock(&tll_lock);
	tll = dev_get_drvdata(tll_dev);

	for (i = 0; i < tll->nch; i++) {
		if (omap_usb_mode_needs_tll(pdata->port_mode[i])) {
			int r;

			if (IS_ERR(tll->ch_clk[i]))
				continue;

			r = clk_enable(tll->ch_clk[i]);
			if (r) {
				dev_err(tll_dev,
				 "Error enabling ch %d clock: %d\n", i, r);
			}
		}
	}

	spin_unlock(&tll_lock);

	return 0;
}