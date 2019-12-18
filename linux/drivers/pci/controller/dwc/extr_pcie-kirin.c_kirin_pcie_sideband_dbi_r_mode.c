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
struct kirin_pcie {int dummy; } ;

/* Variables and functions */
 int PCIE_ELBI_SLV_DBI_ENABLE ; 
 int /*<<< orphan*/  SOC_PCIECTRL_CTRL1_ADDR ; 
 int kirin_apb_ctrl_readl (struct kirin_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kirin_apb_ctrl_writel (struct kirin_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kirin_pcie_sideband_dbi_r_mode(struct kirin_pcie *kirin_pcie,
					   bool on)
{
	u32 val;

	val = kirin_apb_ctrl_readl(kirin_pcie, SOC_PCIECTRL_CTRL1_ADDR);
	if (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_apb_ctrl_writel(kirin_pcie, val, SOC_PCIECTRL_CTRL1_ADDR);
}