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
struct dra7xx_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPTS ; 
 int /*<<< orphan*/  PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MAIN ; 
 int /*<<< orphan*/  PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN ; 
 int /*<<< orphan*/  dra7xx_pcie_writel (struct dra7xx_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dra7xx_pcie_enable_wrapper_interrupts(struct dra7xx_pcie *dra7xx)
{
	dra7xx_pcie_writel(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN,
			   INTERRUPTS);
	dra7xx_pcie_writel(dra7xx, PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MAIN,
			   INTERRUPTS);
}