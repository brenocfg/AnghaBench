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
struct pcie_service_card {scalar_t__ msix_enable; scalar_t__ msi_enable; } ;
struct mwifiex_adapter {int int_status; scalar_t__ ps_state; int pm_wakeup_fw_try; int /*<<< orphan*/  int_lock; int /*<<< orphan*/  wakeup_timer; int /*<<< orphan*/  pps_uapsd_mode; struct pcie_service_card* card; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  PCIE_HOST_INT_STATUS ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_pcie_disable_host_int (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_pcie_ok_to_access_hw (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mwifiex_interrupt_status(struct mwifiex_adapter *adapter,
				     int msg_id)
{
	u32 pcie_ireg;
	unsigned long flags;
	struct pcie_service_card *card = adapter->card;

	if (card->msi_enable) {
		spin_lock_irqsave(&adapter->int_lock, flags);
		adapter->int_status = 1;
		spin_unlock_irqrestore(&adapter->int_lock, flags);
		return;
	}

	if (!mwifiex_pcie_ok_to_access_hw(adapter))
		return;

	if (card->msix_enable && msg_id >= 0) {
		pcie_ireg = BIT(msg_id);
	} else {
		if (mwifiex_read_reg(adapter, PCIE_HOST_INT_STATUS,
				     &pcie_ireg)) {
			mwifiex_dbg(adapter, ERROR, "Read register failed\n");
			return;
		}

		if ((pcie_ireg == 0xFFFFFFFF) || !pcie_ireg)
			return;


		mwifiex_pcie_disable_host_int(adapter);

		/* Clear the pending interrupts */
		if (mwifiex_write_reg(adapter, PCIE_HOST_INT_STATUS,
				      ~pcie_ireg)) {
			mwifiex_dbg(adapter, ERROR,
				    "Write register failed\n");
			return;
		}
	}

	if (!adapter->pps_uapsd_mode &&
	    adapter->ps_state == PS_STATE_SLEEP &&
	    mwifiex_pcie_ok_to_access_hw(adapter)) {
		/* Potentially for PCIe we could get other
		 * interrupts like shared. Don't change power
		 * state until cookie is set
		 */
		adapter->ps_state = PS_STATE_AWAKE;
		adapter->pm_wakeup_fw_try = false;
		del_timer(&adapter->wakeup_timer);
	}

	spin_lock_irqsave(&adapter->int_lock, flags);
	adapter->int_status |= pcie_ireg;
	spin_unlock_irqrestore(&adapter->int_lock, flags);
	mwifiex_dbg(adapter, INTR, "ireg: 0x%08x\n", pcie_ireg);
}