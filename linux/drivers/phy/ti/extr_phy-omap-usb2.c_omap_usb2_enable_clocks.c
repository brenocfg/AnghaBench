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
struct omap_usb {int /*<<< orphan*/  wkupclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  optclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int omap_usb2_enable_clocks(struct omap_usb *phy)
{
	int ret;

	ret = clk_prepare_enable(phy->wkupclk);
	if (ret < 0) {
		dev_err(phy->dev, "Failed to enable wkupclk %d\n", ret);
		goto err0;
	}

	if (!IS_ERR(phy->optclk)) {
		ret = clk_prepare_enable(phy->optclk);
		if (ret < 0) {
			dev_err(phy->dev, "Failed to enable optclk %d\n", ret);
			goto err1;
		}
	}

	return 0;

err1:
	clk_disable(phy->wkupclk);

err0:
	return ret;
}