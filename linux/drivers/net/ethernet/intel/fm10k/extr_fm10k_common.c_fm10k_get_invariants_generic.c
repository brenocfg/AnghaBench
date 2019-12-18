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
struct fm10k_mac_info {int /*<<< orphan*/  max_msix_vectors; int /*<<< orphan*/  dglort_map; } ;
struct fm10k_hw {struct fm10k_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  fm10k_get_pcie_msix_count_generic (struct fm10k_hw*) ; 

s32 fm10k_get_invariants_generic(struct fm10k_hw *hw)
{
	struct fm10k_mac_info *mac = &hw->mac;

	/* initialize GLORT state to avoid any false hits */
	mac->dglort_map = FM10K_DGLORTMAP_NONE;

	/* record maximum number of MSI-X vectors */
	mac->max_msix_vectors = fm10k_get_pcie_msix_count_generic(hw);

	return 0;
}