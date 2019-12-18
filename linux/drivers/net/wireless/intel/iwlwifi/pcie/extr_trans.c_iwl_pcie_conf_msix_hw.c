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
struct iwl_trans_pcie {int /*<<< orphan*/  msix_enabled; struct iwl_trans* trans; } ;
struct iwl_trans {int /*<<< orphan*/  status; TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ mq_rx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  UREG_CHICK ; 
 int /*<<< orphan*/  UREG_CHICK_MSIX_ENABLE ; 
 int /*<<< orphan*/  UREG_CHICK_MSI_ENABLE ; 
 int /*<<< orphan*/  iwl_pcie_map_non_rx_causes (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_map_rx_causes (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_pcie_conf_msix_hw(struct iwl_trans_pcie *trans_pcie)
{
	struct iwl_trans *trans = trans_pcie->trans;

	if (!trans_pcie->msix_enabled) {
		if (trans->trans_cfg->mq_rx_supported &&
		    test_bit(STATUS_DEVICE_ENABLED, &trans->status))
			iwl_write_umac_prph(trans, UREG_CHICK,
					    UREG_CHICK_MSI_ENABLE);
		return;
	}
	/*
	 * The IVAR table needs to be configured again after reset,
	 * but if the device is disabled, we can't write to
	 * prph.
	 */
	if (test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		iwl_write_umac_prph(trans, UREG_CHICK, UREG_CHICK_MSIX_ENABLE);

	/*
	 * Each cause from the causes list above and the RX causes is
	 * represented as a byte in the IVAR table. The first nibble
	 * represents the bound interrupt vector of the cause, the second
	 * represents no auto clear for this cause. This will be set if its
	 * interrupt vector is bound to serve other causes.
	 */
	iwl_pcie_map_rx_causes(trans);

	iwl_pcie_map_non_rx_causes(trans);
}