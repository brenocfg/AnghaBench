#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans_pcie {int def_irq; } ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_causes_list {int /*<<< orphan*/  cause_num; int /*<<< orphan*/  mask_reg; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct iwl_causes_list*) ; 
 int /*<<< orphan*/  CSR_MSIX_IVAR (int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int MSIX_NON_AUTO_CLEAR_CAUSE ; 
 struct iwl_causes_list* causes_list ; 
 struct iwl_causes_list* causes_list_v2 ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write8 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_pcie_map_non_rx_causes(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);
	int val = trans_pcie->def_irq | MSIX_NON_AUTO_CLEAR_CAUSE;
	int i, arr_size =
		(trans->trans_cfg->device_family != IWL_DEVICE_FAMILY_22560) ?
		ARRAY_SIZE(causes_list) : ARRAY_SIZE(causes_list_v2);

	/*
	 * Access all non RX causes and map them to the default irq.
	 * In case we are missing at least one interrupt vector,
	 * the first interrupt vector will serve non-RX and FBQ causes.
	 */
	for (i = 0; i < arr_size; i++) {
		struct iwl_causes_list *causes =
			(trans->trans_cfg->device_family !=
			 IWL_DEVICE_FAMILY_22560) ?
			causes_list : causes_list_v2;

		iwl_write8(trans, CSR_MSIX_IVAR(causes[i].addr), val);
		iwl_clear_bit(trans, causes[i].mask_reg,
			      causes[i].cause_num);
	}
}