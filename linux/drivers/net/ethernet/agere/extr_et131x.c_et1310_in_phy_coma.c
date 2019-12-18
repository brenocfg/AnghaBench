#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct et131x_adapter {TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_csr; } ;
struct TYPE_4__ {TYPE_1__ global; } ;

/* Variables and functions */
 int ET_PM_PHY_SW_COMA ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et1310_in_phy_coma(struct et131x_adapter *adapter)
{
	u32 pmcsr = readl(&adapter->regs->global.pm_csr);

	return ET_PM_PHY_SW_COMA & pmcsr ? 1 : 0;
}