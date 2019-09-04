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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPENSATION_REG1 ; 
 int /*<<< orphan*/  DMA_IP_CTRL_REG ; 
 int /*<<< orphan*/  MASTER_LOCK_REG ; 
 unsigned int MSP_CLK_CTRL_REG ; 
 unsigned int PCIE_SoC_INT_ROUTER_STATUS3_REG ; 
 int /*<<< orphan*/  SPARE3_RESERVED ; 
 int /*<<< orphan*/  SYSTEM_CONFIG_STATUS_REG ; 
 int /*<<< orphan*/  TEST_CTL_REG ; 
 scalar_t__ __reg_within_range (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sta2x11_apb_soc_regs_readable_reg(struct device *dev,
					      unsigned int reg)
{
	return reg <= PCIE_SoC_INT_ROUTER_STATUS3_REG ||
		__reg_within_range(reg, DMA_IP_CTRL_REG, SPARE3_RESERVED) ||
		__reg_within_range(reg, MASTER_LOCK_REG,
				   SYSTEM_CONFIG_STATUS_REG) ||
		reg == MSP_CLK_CTRL_REG ||
		__reg_within_range(reg, COMPENSATION_REG1, TEST_CTL_REG);
}