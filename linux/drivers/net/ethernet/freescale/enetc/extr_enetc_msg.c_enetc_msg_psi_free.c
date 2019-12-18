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
struct enetc_si {int /*<<< orphan*/  pdev; int /*<<< orphan*/  hw; } ;
struct enetc_pf {int num_vfs; int /*<<< orphan*/  msg_task; struct enetc_si* si; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_SI_INT_IDX ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_msg_disable_mr_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_msg_free_mbx (struct enetc_si*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct enetc_si*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void enetc_msg_psi_free(struct enetc_pf *pf)
{
	struct enetc_si *si = pf->si;
	int i;

	cancel_work_sync(&pf->msg_task);

	/* disable MR interrupts */
	enetc_msg_disable_mr_int(&si->hw);

	for (i = 0; i < pf->num_vfs; i++)
		enetc_msg_free_mbx(si, i);

	/* de-register message passing interrupt handler */
	free_irq(pci_irq_vector(si->pdev, ENETC_SI_INT_IDX), si);
}