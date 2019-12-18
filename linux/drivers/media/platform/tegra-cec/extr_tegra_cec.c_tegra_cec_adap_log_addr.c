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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_cec {int dummy; } ;
struct cec_adapter {struct tegra_cec* priv; } ;

/* Variables and functions */
 int CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  TEGRA_CEC_HWCTRL_RX_LADDR (int) ; 
 int /*<<< orphan*/  TEGRA_CEC_HWCTRL_RX_LADDR_MASK ; 
 int /*<<< orphan*/  TEGRA_CEC_HW_CONTROL ; 
 int /*<<< orphan*/  cec_read (struct tegra_cec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_write (struct tegra_cec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_cec_adap_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	struct tegra_cec *cec = adap->priv;
	u32 state = cec_read(cec, TEGRA_CEC_HW_CONTROL);

	if (logical_addr == CEC_LOG_ADDR_INVALID)
		state &= ~TEGRA_CEC_HWCTRL_RX_LADDR_MASK;
	else
		state |= TEGRA_CEC_HWCTRL_RX_LADDR((1 << logical_addr));

	cec_write(cec, TEGRA_CEC_HW_CONTROL, state);
	return 0;
}