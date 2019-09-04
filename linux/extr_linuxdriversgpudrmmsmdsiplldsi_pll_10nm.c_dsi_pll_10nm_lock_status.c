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
typedef  int u32 ;
struct dsi_pll_10nm {int /*<<< orphan*/  id; scalar_t__ mmio; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_DSI_10nm_PHY_PLL_COMMON_STATUS_ONE ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int const,int const) ; 

__attribute__((used)) static int dsi_pll_10nm_lock_status(struct dsi_pll_10nm *pll)
{
	int rc;
	u32 status = 0;
	u32 const delay_us = 100;
	u32 const timeout_us = 5000;

	rc = readl_poll_timeout_atomic(pll->mmio +
				       REG_DSI_10nm_PHY_PLL_COMMON_STATUS_ONE,
				       status,
				       ((status & BIT(0)) > 0),
				       delay_us,
				       timeout_us);
	if (rc)
		pr_err("DSI PLL(%d) lock failed, status=0x%08x\n",
		       pll->id, status);

	return rc;
}