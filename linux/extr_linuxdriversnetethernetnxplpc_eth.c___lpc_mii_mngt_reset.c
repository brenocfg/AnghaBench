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
struct netdata_local {int /*<<< orphan*/  net_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC_ENET_MCFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_MCFG_CLOCK_HOST_DIV_28 ; 
 int /*<<< orphan*/  LPC_MCFG_CLOCK_SELECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_MCFG_RESET_MII_MGMT ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __lpc_mii_mngt_reset(struct netdata_local *pldat)
{
	/* Reset MII management hardware */
	writel(LPC_MCFG_RESET_MII_MGMT, LPC_ENET_MCFG(pldat->net_base));

	/* Setup MII clock to slowest rate with a /28 divider */
	writel(LPC_MCFG_CLOCK_SELECT(LPC_MCFG_CLOCK_HOST_DIV_28),
	       LPC_ENET_MCFG(pldat->net_base));

	return 0;
}