#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct et131x_adapter {TYPE_3__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  cfg1; } ;
struct TYPE_4__ {int /*<<< orphan*/  sw_reset; } ;
struct TYPE_6__ {TYPE_2__ mac; TYPE_1__ global; } ;

/* Variables and functions */
 int ET_MAC_CFG1_RESET_RXFUNC ; 
 int ET_MAC_CFG1_RESET_RXMC ; 
 int ET_MAC_CFG1_RESET_TXFUNC ; 
 int ET_MAC_CFG1_RESET_TXMC ; 
 int ET_MAC_CFG1_SIM_RESET ; 
 int ET_MAC_CFG1_SOFT_RESET ; 
 int ET_RESET_ALL ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_soft_reset(struct et131x_adapter *adapter)
{
	u32 reg;

	/* Disable MAC Core */
	reg = ET_MAC_CFG1_SOFT_RESET | ET_MAC_CFG1_SIM_RESET |
	      ET_MAC_CFG1_RESET_RXMC | ET_MAC_CFG1_RESET_TXMC |
	      ET_MAC_CFG1_RESET_RXFUNC | ET_MAC_CFG1_RESET_TXFUNC;
	writel(reg, &adapter->regs->mac.cfg1);

	reg = ET_RESET_ALL;
	writel(reg, &adapter->regs->global.sw_reset);

	reg = ET_MAC_CFG1_RESET_RXMC | ET_MAC_CFG1_RESET_TXMC |
	      ET_MAC_CFG1_RESET_RXFUNC | ET_MAC_CFG1_RESET_TXFUNC;
	writel(reg, &adapter->regs->mac.cfg1);
	writel(0, &adapter->regs->mac.cfg1);
}