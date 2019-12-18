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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct iproc_msi_grp {int eq; struct iproc_msi* msi; } ;
struct iproc_msi {int /*<<< orphan*/  inner_domain; } ;

/* Variables and functions */
 int EQ_LEN ; 
 int /*<<< orphan*/  IPROC_MSI_EQ_HEAD ; 
 int IPROC_MSI_EQ_MASK ; 
 int /*<<< orphan*/  IPROC_MSI_EQ_TAIL ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 unsigned long decode_msi_hwirq (struct iproc_msi*,int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int iproc_msi_read_reg (struct iproc_msi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iproc_msi_write_reg (struct iproc_msi*,int /*<<< orphan*/ ,int,int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct iproc_msi_grp* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void iproc_msi_handler(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct iproc_msi_grp *grp;
	struct iproc_msi *msi;
	u32 eq, head, tail, nr_events;
	unsigned long hwirq;
	int virq;

	chained_irq_enter(chip, desc);

	grp = irq_desc_get_handler_data(desc);
	msi = grp->msi;
	eq = grp->eq;

	/*
	 * iProc MSI event queue is tracked by head and tail pointers.  Head
	 * pointer indicates the next entry (MSI data) to be consumed by SW in
	 * the queue and needs to be updated by SW.  iProc MSI core uses the
	 * tail pointer as the next data insertion point.
	 *
	 * Entries between head and tail pointers contain valid MSI data.  MSI
	 * data is guaranteed to be in the event queue memory before the tail
	 * pointer is updated by the iProc MSI core.
	 */
	head = iproc_msi_read_reg(msi, IPROC_MSI_EQ_HEAD,
				  eq) & IPROC_MSI_EQ_MASK;
	do {
		tail = iproc_msi_read_reg(msi, IPROC_MSI_EQ_TAIL,
					  eq) & IPROC_MSI_EQ_MASK;

		/*
		 * Figure out total number of events (MSI data) to be
		 * processed.
		 */
		nr_events = (tail < head) ?
			(EQ_LEN - (head - tail)) : (tail - head);
		if (!nr_events)
			break;

		/* process all outstanding events */
		while (nr_events--) {
			hwirq = decode_msi_hwirq(msi, eq, head);
			virq = irq_find_mapping(msi->inner_domain, hwirq);
			generic_handle_irq(virq);

			head++;
			head %= EQ_LEN;
		}

		/*
		 * Now all outstanding events have been processed.  Update the
		 * head pointer.
		 */
		iproc_msi_write_reg(msi, IPROC_MSI_EQ_HEAD, eq, head);

		/*
		 * Now go read the tail pointer again to see if there are new
		 * outstanding events that came in during the above window.
		 */
	} while (true);

	chained_irq_exit(chip, desc);
}