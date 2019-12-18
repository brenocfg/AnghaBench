#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct iwl_trans_pcie_removal {int /*<<< orphan*/  work; int /*<<< orphan*/  pdev; } ;
struct iwl_trans_pcie {int /*<<< orphan*/  reg_lock; scalar_t__ cmd_hold_nic_awake; } ;
struct iwl_trans {int /*<<< orphan*/  dev; int /*<<< orphan*/  status; TYPE_2__* trans_cfg; } ;
struct TYPE_6__ {scalar_t__ remove_when_gone; } ;
struct TYPE_5__ {scalar_t__ device_family; TYPE_1__* csr; } ;
struct TYPE_4__ {int /*<<< orphan*/  flag_mac_clock_ready; int /*<<< orphan*/  flag_val_mac_access_en; int /*<<< orphan*/  flag_mac_access_req; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_FORCE_NMI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_TRANS_DEAD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int,int,int) ; 
 unsigned int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_dump_regs (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_removal_wk ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ iwlwifi_mod_params ; 
 struct iwl_trans_pcie_removal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool iwl_trans_pcie_grab_nic_access(struct iwl_trans *trans,
					   unsigned long *flags)
{
	int ret;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_irqsave(&trans_pcie->reg_lock, *flags);

	if (trans_pcie->cmd_hold_nic_awake)
		goto out;

	/* this bit wakes up the NIC */
	__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
				 BIT(trans->trans_cfg->csr->flag_mac_access_req));
	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
		udelay(2);

	/*
	 * These bits say the device is running, and should keep running for
	 * at least a short while (at least as long as MAC_ACCESS_REQ stays 1),
	 * but they do not indicate that embedded SRAM is restored yet;
	 * HW with volatile SRAM must save/restore contents to/from
	 * host DRAM when sleeping/waking for power-saving.
	 * Each direction takes approximately 1/4 millisecond; with this
	 * overhead, it's a good idea to grab and hold MAC_ACCESS_REQUEST if a
	 * series of register accesses are expected (e.g. reading Event Log),
	 * to keep device from sleeping.
	 *
	 * CSR_UCODE_DRV_GP1 register bit MAC_SLEEP == 0 indicates that
	 * SRAM is okay/restored.  We don't check that here because this call
	 * is just for hardware register access; but GP1 MAC_SLEEP
	 * check is a good idea before accessing the SRAM of HW with
	 * volatile SRAM (e.g. reading Event Log).
	 *
	 * 5000 series and later (including 1000 series) have non-volatile SRAM,
	 * and do not save/restore SRAM when power cycling.
	 */
	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   BIT(trans->trans_cfg->csr->flag_val_mac_access_en),
			   (BIT(trans->trans_cfg->csr->flag_mac_clock_ready) |
			    CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	if (unlikely(ret < 0)) {
		u32 cntrl = iwl_read32(trans, CSR_GP_CNTRL);

		WARN_ONCE(1,
			  "Timeout waiting for hardware access (CSR_GP_CNTRL 0x%08x)\n",
			  cntrl);

		iwl_trans_pcie_dump_regs(trans);

		if (iwlwifi_mod_params.remove_when_gone && cntrl == ~0U) {
			struct iwl_trans_pcie_removal *removal;

			if (test_bit(STATUS_TRANS_DEAD, &trans->status))
				goto err;

			IWL_ERR(trans, "Device gone - scheduling removal!\n");

			/*
			 * get a module reference to avoid doing this
			 * while unloading anyway and to avoid
			 * scheduling a work with code that's being
			 * removed.
			 */
			if (!try_module_get(THIS_MODULE)) {
				IWL_ERR(trans,
					"Module is being unloaded - abort\n");
				goto err;
			}

			removal = kzalloc(sizeof(*removal), GFP_ATOMIC);
			if (!removal) {
				module_put(THIS_MODULE);
				goto err;
			}
			/*
			 * we don't need to clear this flag, because
			 * the trans will be freed and reallocated.
			*/
			set_bit(STATUS_TRANS_DEAD, &trans->status);

			removal->pdev = to_pci_dev(trans->dev);
			INIT_WORK(&removal->work, iwl_trans_pcie_removal_wk);
			pci_dev_get(removal->pdev);
			schedule_work(&removal->work);
		} else {
			iwl_write32(trans, CSR_RESET,
				    CSR_RESET_REG_FLAG_FORCE_NMI);
		}

err:
		spin_unlock_irqrestore(&trans_pcie->reg_lock, *flags);
		return false;
	}

out:
	/*
	 * Fool sparse by faking we release the lock - sparse will
	 * track nic_access anyway.
	 */
	__release(&trans_pcie->reg_lock);
	return true;
}