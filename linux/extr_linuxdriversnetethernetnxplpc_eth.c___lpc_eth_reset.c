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
 int LPC_COMMAND_REG_RESET ; 
 int LPC_COMMAND_RXRESET ; 
 int LPC_COMMAND_TXRESET ; 
 int /*<<< orphan*/  LPC_ENET_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC1 (int /*<<< orphan*/ ) ; 
 int LPC_MAC1_RESET_MCS_RX ; 
 int LPC_MAC1_RESET_MCS_TX ; 
 int LPC_MAC1_RESET_RX ; 
 int LPC_MAC1_RESET_TX ; 
 int LPC_MAC1_SIMULATION_RESET ; 
 int LPC_MAC1_SOFT_RESET ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lpc_eth_reset(struct netdata_local *pldat)
{
	/* Reset all MAC logic */
	writel((LPC_MAC1_RESET_TX | LPC_MAC1_RESET_MCS_TX | LPC_MAC1_RESET_RX |
		LPC_MAC1_RESET_MCS_RX | LPC_MAC1_SIMULATION_RESET |
		LPC_MAC1_SOFT_RESET), LPC_ENET_MAC1(pldat->net_base));
	writel((LPC_COMMAND_REG_RESET | LPC_COMMAND_TXRESET |
		LPC_COMMAND_RXRESET), LPC_ENET_COMMAND(pldat->net_base));
}