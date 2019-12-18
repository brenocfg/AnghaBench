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
typedef  int u32 ;
struct netdata_local {int /*<<< orphan*/  ndev; int /*<<< orphan*/  net_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC_ENET_SA0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_SA1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_SA2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lpc_set_mac(struct netdata_local *pldat, u8 *mac)
{
	u32 tmp;

	/* Set station address */
	tmp = mac[0] | ((u32)mac[1] << 8);
	writel(tmp, LPC_ENET_SA2(pldat->net_base));
	tmp = mac[2] | ((u32)mac[3] << 8);
	writel(tmp, LPC_ENET_SA1(pldat->net_base));
	tmp = mac[4] | ((u32)mac[5] << 8);
	writel(tmp, LPC_ENET_SA0(pldat->net_base));

	netdev_dbg(pldat->ndev, "Ethernet MAC address %pM\n", mac);
}