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
struct ath10k {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ath10k_pci_disable_and_clear_legacy_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_msi_fw_mask (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_pending (struct ath10k*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ath10k_ahb_interrupt_handler(int irq, void *arg)
{
	struct ath10k *ar = arg;

	if (!ath10k_pci_irq_pending(ar))
		return IRQ_NONE;

	ath10k_pci_disable_and_clear_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_mask(ar);
	napi_schedule(&ar->napi);

	return IRQ_HANDLED;
}