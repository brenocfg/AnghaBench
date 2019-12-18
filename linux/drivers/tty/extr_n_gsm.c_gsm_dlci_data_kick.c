#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gsm_dlci {TYPE_1__* gsm; scalar_t__ net; scalar_t__ constipated; } ;
struct TYPE_4__ {scalar_t__ tx_bytes; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 scalar_t__ TX_THRESH_LO ; 
 int /*<<< orphan*/  gsm_dlci_data_output (TYPE_1__*,struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_dlci_data_output_framed (TYPE_1__*,struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_dlci_data_sweep (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gsm_dlci_data_kick(struct gsm_dlci *dlci)
{
	unsigned long flags;
	int sweep;

	if (dlci->constipated)
		return;

	spin_lock_irqsave(&dlci->gsm->tx_lock, flags);
	/* If we have nothing running then we need to fire up */
	sweep = (dlci->gsm->tx_bytes < TX_THRESH_LO);
	if (dlci->gsm->tx_bytes == 0) {
		if (dlci->net)
			gsm_dlci_data_output_framed(dlci->gsm, dlci);
		else
			gsm_dlci_data_output(dlci->gsm, dlci);
	}
	if (sweep)
		gsm_dlci_data_sweep(dlci->gsm);
	spin_unlock_irqrestore(&dlci->gsm->tx_lock, flags);
}