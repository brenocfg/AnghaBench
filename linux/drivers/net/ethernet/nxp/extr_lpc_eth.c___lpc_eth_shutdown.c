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
 int /*<<< orphan*/  LPC_ENET_MAC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lpc_eth_reset (struct netdata_local*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lpc_eth_shutdown(struct netdata_local *pldat)
{
	/* Reset ethernet and power down PHY */
	__lpc_eth_reset(pldat);
	writel(0, LPC_ENET_MAC1(pldat->net_base));
	writel(0, LPC_ENET_MAC2(pldat->net_base));
}