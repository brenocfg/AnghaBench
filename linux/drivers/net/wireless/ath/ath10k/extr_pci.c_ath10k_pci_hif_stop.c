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
struct ath10k_pci {scalar_t__ ps_wake_refcount; int /*<<< orphan*/  ps_lock; } ;
struct ath10k {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_pci_flush (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_disable (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_sync (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_safe_chip_reset (struct ath10k*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath10k_pci_hif_stop(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	unsigned long flags;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif stop\n");

	ath10k_pci_irq_disable(ar);
	ath10k_pci_irq_sync(ar);
	napi_synchronize(&ar->napi);
	napi_disable(&ar->napi);

	/* Most likely the device has HTT Rx ring configured. The only way to
	 * prevent the device from accessing (and possible corrupting) host
	 * memory is to reset the chip now.
	 *
	 * There's also no known way of masking MSI interrupts on the device.
	 * For ranged MSI the CE-related interrupts can be masked. However
	 * regardless how many MSI interrupts are assigned the first one
	 * is always used for firmware indications (crashes) and cannot be
	 * masked. To prevent the device from asserting the interrupt reset it
	 * before proceeding with cleanup.
	 */
	ath10k_pci_safe_chip_reset(ar);

	ath10k_pci_flush(ar);

	spin_lock_irqsave(&ar_pci->ps_lock, flags);
	WARN_ON(ar_pci->ps_wake_refcount > 0);
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
}