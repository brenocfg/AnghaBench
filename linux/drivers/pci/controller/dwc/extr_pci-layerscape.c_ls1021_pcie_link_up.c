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
struct ls_pcie {int /*<<< orphan*/  index; int /*<<< orphan*/  scfg; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int LTSSM_PCIE_L0 ; 
 int LTSSM_STATE_MASK ; 
 int LTSSM_STATE_SHIFT ; 
 int /*<<< orphan*/  SCFG_PEXMSCPORTSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct ls_pcie* to_ls_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ls1021_pcie_link_up(struct dw_pcie *pci)
{
	u32 state;
	struct ls_pcie *pcie = to_ls_pcie(pci);

	if (!pcie->scfg)
		return 0;

	regmap_read(pcie->scfg, SCFG_PEXMSCPORTSR(pcie->index), &state);
	state = (state >> LTSSM_STATE_SHIFT) & LTSSM_STATE_MASK;

	if (state < LTSSM_PCIE_L0)
		return 0;

	return 1;
}