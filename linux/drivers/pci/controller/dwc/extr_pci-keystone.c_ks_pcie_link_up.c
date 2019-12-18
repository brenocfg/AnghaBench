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
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PORT_DEBUG0 ; 
 int /*<<< orphan*/  PORT_LOGIC_LTSSM_STATE_L0 ; 
 int /*<<< orphan*/  PORT_LOGIC_LTSSM_STATE_MASK ; 
 int /*<<< orphan*/  dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks_pcie_link_up(struct dw_pcie *pci)
{
	u32 val;

	val = dw_pcie_readl_dbi(pci, PCIE_PORT_DEBUG0);
	val &= PORT_LOGIC_LTSSM_STATE_MASK;
	return (val == PORT_LOGIC_LTSSM_STATE_L0);
}