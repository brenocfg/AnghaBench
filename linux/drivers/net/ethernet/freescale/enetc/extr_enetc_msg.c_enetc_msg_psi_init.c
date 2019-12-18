#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct enetc_si {int /*<<< orphan*/  hw; TYPE_2__* pdev; TYPE_1__* ndev; } ;
struct enetc_pf {int num_vfs; int /*<<< orphan*/  msg_task; int /*<<< orphan*/  msg_int_name; struct enetc_si* si; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_SIMSIVR ; 
 int /*<<< orphan*/  ENETC_SI_INT_IDX ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int enetc_msg_alloc_mbx (struct enetc_si*,int) ; 
 int /*<<< orphan*/  enetc_msg_enable_mr_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_msg_free_mbx (struct enetc_si*,int) ; 
 int /*<<< orphan*/  enetc_msg_psi_msix ; 
 int /*<<< orphan*/  enetc_msg_task ; 
 int /*<<< orphan*/  enetc_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct enetc_si*) ; 
 int pci_irq_vector (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct enetc_si*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

int enetc_msg_psi_init(struct enetc_pf *pf)
{
	struct enetc_si *si = pf->si;
	int vector, i, err;

	/* register message passing interrupt handler */
	snprintf(pf->msg_int_name, sizeof(pf->msg_int_name), "%s-vfmsg",
		 si->ndev->name);
	vector = pci_irq_vector(si->pdev, ENETC_SI_INT_IDX);
	err = request_irq(vector, enetc_msg_psi_msix, 0, pf->msg_int_name, si);
	if (err) {
		dev_err(&si->pdev->dev,
			"PSI messaging: request_irq() failed!\n");
		return err;
	}

	/* set one IRQ entry for PSI message receive notification (SI int) */
	enetc_wr(&si->hw, ENETC_SIMSIVR, ENETC_SI_INT_IDX);

	/* initialize PSI mailbox */
	INIT_WORK(&pf->msg_task, enetc_msg_task);

	for (i = 0; i < pf->num_vfs; i++) {
		err = enetc_msg_alloc_mbx(si, i);
		if (err)
			goto err_init_mbx;
	}

	/* enable MR interrupts */
	enetc_msg_enable_mr_int(&si->hw);

	return 0;

err_init_mbx:
	for (i--; i >= 0; i--)
		enetc_msg_free_mbx(si, i);

	free_irq(vector, si);

	return err;
}