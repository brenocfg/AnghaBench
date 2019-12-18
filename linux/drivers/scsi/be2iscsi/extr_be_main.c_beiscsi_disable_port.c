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
struct hwi_controller {struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {struct be_eq_obj* be_eq; } ;
struct beiscsi_hba {unsigned int num_cpus; int /*<<< orphan*/  boot_work; int /*<<< orphan*/  eqd_update; int /*<<< orphan*/  pcidev; struct hwi_controller* phwi_ctrlr; int /*<<< orphan*/  state; } ;
struct be_eq_obj {int /*<<< orphan*/  mcc_work; int /*<<< orphan*/  iopoll; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_ONLINE ; 
 int /*<<< orphan*/  beiscsi_cleanup_port (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_free_irqs (struct beiscsi_hba*) ; 
 scalar_t__ beiscsi_hba_in_error (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwi_cleanup_port (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_disable_intr (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_disable_port(struct beiscsi_hba *phba, int unload)
{
	struct hwi_context_memory *phwi_context;
	struct hwi_controller *phwi_ctrlr;
	struct be_eq_obj *pbe_eq;
	unsigned int i;

	if (!test_and_clear_bit(BEISCSI_HBA_ONLINE, &phba->state))
		return;

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;
	hwi_disable_intr(phba);
	beiscsi_free_irqs(phba);
	pci_free_irq_vectors(phba->pcidev);

	for (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		irq_poll_disable(&pbe_eq->iopoll);
	}
	cancel_delayed_work_sync(&phba->eqd_update);
	cancel_work_sync(&phba->boot_work);
	/* WQ might be running cancel queued mcc_work if we are not exiting */
	if (!unload && beiscsi_hba_in_error(phba)) {
		pbe_eq = &phwi_context->be_eq[i];
		cancel_work_sync(&pbe_eq->mcc_work);
	}
	hwi_cleanup_port(phba);
	beiscsi_cleanup_port(phba);
}