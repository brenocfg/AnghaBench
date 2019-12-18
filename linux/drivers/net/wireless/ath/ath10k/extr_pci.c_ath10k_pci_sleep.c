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
struct ath10k_pci {scalar_t__ pci_ps; scalar_t__ ps_wake_refcount; int /*<<< orphan*/  ps_lock; int /*<<< orphan*/  ps_timer; int /*<<< orphan*/  ps_awake; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_PCI_PS ; 
 int /*<<< orphan*/  ATH10K_PCI_SLEEP_GRACE_PERIOD_MSEC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath10k_pci_sleep(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	unsigned long flags;

	if (ar_pci->pci_ps == 0)
		return;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps sleep refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	if (WARN_ON(ar_pci->ps_wake_refcount == 0))
		goto skip;

	ar_pci->ps_wake_refcount--;

	mod_timer(&ar_pci->ps_timer, jiffies +
		  msecs_to_jiffies(ATH10K_PCI_SLEEP_GRACE_PERIOD_MSEC));

skip:
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
}