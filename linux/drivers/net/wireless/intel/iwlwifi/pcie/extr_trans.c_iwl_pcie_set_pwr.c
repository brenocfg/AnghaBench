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
struct iwl_trans {int /*<<< orphan*/  dev; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ apmg_not_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_MSK_PWR_SRC ; 
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_PWR_SRC_VAUX ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_PWR_SRC_VMAIN ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  iwl_set_bits_mask_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_pme_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_pcie_set_pwr(struct iwl_trans *trans, bool vaux)
{
	if (trans->cfg->apmg_not_supported)
		return;

	if (vaux && pci_pme_capable(to_pci_dev(trans->dev), PCI_D3cold))
		iwl_set_bits_mask_prph(trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_VAL_PWR_SRC_VAUX,
				       ~APMG_PS_CTRL_MSK_PWR_SRC);
	else
		iwl_set_bits_mask_prph(trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_VAL_PWR_SRC_VMAIN,
				       ~APMG_PS_CTRL_MSK_PWR_SRC);
}