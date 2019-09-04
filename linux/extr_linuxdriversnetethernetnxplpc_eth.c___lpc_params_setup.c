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
struct netdata_local {scalar_t__ duplex; scalar_t__ speed; int /*<<< orphan*/  net_base; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  LPC_COMMAND_FULLDUPLEX ; 
 int /*<<< orphan*/  LPC_ENET_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_IPGT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_SUPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_IPGT_LOAD (int) ; 
 int /*<<< orphan*/  LPC_MAC2_FULL_DUPLEX ; 
 int /*<<< orphan*/  LPC_SUPP_SPEED ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lpc_params_setup(struct netdata_local *pldat)
{
	u32 tmp;

	if (pldat->duplex == DUPLEX_FULL) {
		tmp = readl(LPC_ENET_MAC2(pldat->net_base));
		tmp |= LPC_MAC2_FULL_DUPLEX;
		writel(tmp, LPC_ENET_MAC2(pldat->net_base));
		tmp = readl(LPC_ENET_COMMAND(pldat->net_base));
		tmp |= LPC_COMMAND_FULLDUPLEX;
		writel(tmp, LPC_ENET_COMMAND(pldat->net_base));
		writel(LPC_IPGT_LOAD(0x15), LPC_ENET_IPGT(pldat->net_base));
	} else {
		tmp = readl(LPC_ENET_MAC2(pldat->net_base));
		tmp &= ~LPC_MAC2_FULL_DUPLEX;
		writel(tmp, LPC_ENET_MAC2(pldat->net_base));
		tmp = readl(LPC_ENET_COMMAND(pldat->net_base));
		tmp &= ~LPC_COMMAND_FULLDUPLEX;
		writel(tmp, LPC_ENET_COMMAND(pldat->net_base));
		writel(LPC_IPGT_LOAD(0x12), LPC_ENET_IPGT(pldat->net_base));
	}

	if (pldat->speed == SPEED_100)
		writel(LPC_SUPP_SPEED, LPC_ENET_SUPP(pldat->net_base));
	else
		writel(0, LPC_ENET_SUPP(pldat->net_base));
}