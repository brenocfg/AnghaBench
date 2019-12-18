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
struct stm32_dwmac {scalar_t__ clk_eth_ck; scalar_t__ syscfg_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 

__attribute__((used)) static int stm32mp1_clk_prepare(struct stm32_dwmac *dwmac, bool prepare)
{
	int ret = 0;

	if (prepare) {
		ret = clk_prepare_enable(dwmac->syscfg_clk);
		if (ret)
			return ret;

		if (dwmac->clk_eth_ck) {
			ret = clk_prepare_enable(dwmac->clk_eth_ck);
			if (ret) {
				clk_disable_unprepare(dwmac->syscfg_clk);
				return ret;
			}
		}
	} else {
		clk_disable_unprepare(dwmac->syscfg_clk);
		if (dwmac->clk_eth_ck)
			clk_disable_unprepare(dwmac->clk_eth_ck);
	}
	return ret;
}