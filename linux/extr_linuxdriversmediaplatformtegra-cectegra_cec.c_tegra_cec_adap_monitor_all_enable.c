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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_cec {int dummy; } ;
struct cec_adapter {struct tegra_cec* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_CEC_HWCTRL_RX_SNOOP ; 
 int /*<<< orphan*/  TEGRA_CEC_HW_CONTROL ; 
 int /*<<< orphan*/  cec_read (struct tegra_cec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_write (struct tegra_cec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_cec_adap_monitor_all_enable(struct cec_adapter *adap,
					     bool enable)
{
	struct tegra_cec *cec = adap->priv;
	u32 reg = cec_read(cec, TEGRA_CEC_HW_CONTROL);

	if (enable)
		reg |= TEGRA_CEC_HWCTRL_RX_SNOOP;
	else
		reg &= ~TEGRA_CEC_HWCTRL_RX_SNOOP;
	cec_write(cec, TEGRA_CEC_HW_CONTROL, reg);
	return 0;
}