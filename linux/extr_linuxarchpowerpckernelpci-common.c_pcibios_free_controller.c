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
struct pci_controller {scalar_t__ global_number; scalar_t__ is_dynamic; int /*<<< orphan*/  list_node; } ;

/* Variables and functions */
 scalar_t__ MAX_PHBS ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hose_spinlock ; 
 int /*<<< orphan*/  kfree (struct pci_controller*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phb_bitmap ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pcibios_free_controller(struct pci_controller *phb)
{
	spin_lock(&hose_spinlock);

	/* Clear bit of phb_bitmap to allow reuse of this PHB number. */
	if (phb->global_number < MAX_PHBS)
		clear_bit(phb->global_number, phb_bitmap);

	list_del(&phb->list_node);
	spin_unlock(&hose_spinlock);

	if (phb->is_dynamic)
		kfree(phb);
}