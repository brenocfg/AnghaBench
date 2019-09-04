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
typedef  int u16 ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_PCIE_SRIOV_CTRL ; 
 int FM10K_PCIE_SRIOV_CTRL_VFARI ; 
 int fm10k_read_pci_cfg_word (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fm10k_is_ari_hierarchy_pf(struct fm10k_hw *hw)
{
	u16 sriov_ctrl = fm10k_read_pci_cfg_word(hw, FM10K_PCIE_SRIOV_CTRL);

	return !!(sriov_ctrl & FM10K_PCIE_SRIOV_CTRL_VFARI);
}