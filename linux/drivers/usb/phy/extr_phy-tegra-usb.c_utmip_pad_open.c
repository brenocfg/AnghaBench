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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional_shared (int /*<<< orphan*/ ,char*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  utmip_pad_lock ; 

__attribute__((used)) static int utmip_pad_open(struct tegra_usb_phy *phy)
{
	int ret;

	phy->pad_clk = devm_clk_get(phy->u_phy.dev, "utmi-pads");
	if (IS_ERR(phy->pad_clk)) {
		ret = PTR_ERR(phy->pad_clk);
		dev_err(phy->u_phy.dev,
			"Failed to get UTMIP pad clock: %d\n", ret);
		return ret;
	}

	phy->pad_rst = devm_reset_control_get_optional_shared(
						phy->u_phy.dev, "utmi-pads");
	if (IS_ERR(phy->pad_rst)) {
		ret = PTR_ERR(phy->pad_rst);
		dev_err(phy->u_phy.dev,
			"Failed to get UTMI-pads reset: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(phy->pad_clk);
	if (ret) {
		dev_err(phy->u_phy.dev,
			"Failed to enable UTMI-pads clock: %d\n", ret);
		return ret;
	}

	spin_lock(&utmip_pad_lock);

	ret = reset_control_deassert(phy->pad_rst);
	if (ret) {
		dev_err(phy->u_phy.dev,
			"Failed to initialize UTMI-pads reset: %d\n", ret);
		goto unlock;
	}

	ret = reset_control_assert(phy->pad_rst);
	if (ret) {
		dev_err(phy->u_phy.dev,
			"Failed to assert UTMI-pads reset: %d\n", ret);
		goto unlock;
	}

	udelay(1);

	ret = reset_control_deassert(phy->pad_rst);
	if (ret)
		dev_err(phy->u_phy.dev,
			"Failed to deassert UTMI-pads reset: %d\n", ret);
unlock:
	spin_unlock(&utmip_pad_lock);

	clk_disable_unprepare(phy->pad_clk);

	return ret;
}