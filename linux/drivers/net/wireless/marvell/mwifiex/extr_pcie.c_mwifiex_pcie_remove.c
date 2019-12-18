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
typedef  int u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {TYPE_1__ pcie; struct mwifiex_adapter* adapter; int /*<<< orphan*/  fw_done; } ;
struct pci_dev {int dummy; } ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_pcie_card_reg {int /*<<< orphan*/  fw_status; } ;
struct mwifiex_adapter {int /*<<< orphan*/  mfg_mode; int /*<<< orphan*/  priv_num; } ;

/* Variables and functions */
 int FIRMWARE_READY_PCIE ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 int /*<<< orphan*/  MWIFIEX_FUNC_SHUTDOWN ; 
 int /*<<< orphan*/  mwifiex_deauthenticate_all (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_disable_auto_ds (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_init_shutdown_fw (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mwifiex_remove_card (struct mwifiex_adapter*) ; 
 struct pcie_service_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_pcie_remove(struct pci_dev *pdev)
{
	struct pcie_service_card *card;
	struct mwifiex_adapter *adapter;
	struct mwifiex_private *priv;
	const struct mwifiex_pcie_card_reg *reg;
	u32 fw_status;
	int ret;

	card = pci_get_drvdata(pdev);

	wait_for_completion(&card->fw_done);

	adapter = card->adapter;
	if (!adapter || !adapter->priv_num)
		return;

	reg = card->pcie.reg;
	if (reg)
		ret = mwifiex_read_reg(adapter, reg->fw_status, &fw_status);
	else
		fw_status = -1;

	if (fw_status == FIRMWARE_READY_PCIE && !adapter->mfg_mode) {
		mwifiex_deauthenticate_all(adapter);

		priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

		mwifiex_disable_auto_ds(priv);

		mwifiex_init_shutdown_fw(priv, MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_remove_card(adapter);
}