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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct tegra_usb_phy {int /*<<< orphan*/  pad_clk; TYPE_1__ u_phy; int /*<<< orphan*/  pad_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int utmip_pad_close(struct tegra_usb_phy *phy)
{
	int ret;

	ret = clk_prepare_enable(phy->pad_clk);
	if (ret) {
		dev_err(phy->u_phy.dev,
			"Failed to enable UTMI-pads clock: %d\n", ret);
		return ret;
	}

	ret = reset_control_assert(phy->pad_rst);
	if (ret)
		dev_err(phy->u_phy.dev,
			"Failed to assert UTMI-pads reset: %d\n", ret);

	udelay(1);

	clk_disable_unprepare(phy->pad_clk);

	return ret;
}