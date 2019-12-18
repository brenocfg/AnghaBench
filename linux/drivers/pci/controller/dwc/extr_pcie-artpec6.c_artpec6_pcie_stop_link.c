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
struct artpec6_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIECFG ; 
 int /*<<< orphan*/  PCIECFG_LTSSM_ENABLE ; 
 int /*<<< orphan*/  artpec6_pcie_readl (struct artpec6_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_pcie_writel (struct artpec6_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct artpec6_pcie* to_artpec6_pcie (struct dw_pcie*) ; 

__attribute__((used)) static void artpec6_pcie_stop_link(struct dw_pcie *pci)
{
	struct artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	u32 val;

	val = artpec6_pcie_readl(artpec6_pcie, PCIECFG);
	val &= ~PCIECFG_LTSSM_ENABLE;
	artpec6_pcie_writel(artpec6_pcie, PCIECFG, val);
}