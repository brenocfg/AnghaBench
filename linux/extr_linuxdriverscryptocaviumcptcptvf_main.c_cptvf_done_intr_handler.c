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
typedef  scalar_t__ u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cptvf_wqe {int /*<<< orphan*/  twork; } ;
struct cpt_vf {int /*<<< orphan*/  vfid; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ cptvf_read_vq_done_count (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_write_vq_done_ack (struct cpt_vf*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct cptvf_wqe* get_cptvf_vq_wqe (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t cptvf_done_intr_handler(int irq, void *cptvf_irq)
{
	struct cpt_vf *cptvf = (struct cpt_vf *)cptvf_irq;
	struct pci_dev *pdev = cptvf->pdev;
	/* Read the number of completions */
	u32 intr = cptvf_read_vq_done_count(cptvf);

	if (intr) {
		struct cptvf_wqe *wqe;

		/* Acknowledge the number of
		 * scheduled completions for processing
		 */
		cptvf_write_vq_done_ack(cptvf, intr);
		wqe = get_cptvf_vq_wqe(cptvf, 0);
		if (unlikely(!wqe)) {
			dev_err(&pdev->dev, "No work to schedule for VF (%d)",
				cptvf->vfid);
			return IRQ_NONE;
		}
		tasklet_hi_schedule(&wqe->twork);
	}

	return IRQ_HANDLED;
}