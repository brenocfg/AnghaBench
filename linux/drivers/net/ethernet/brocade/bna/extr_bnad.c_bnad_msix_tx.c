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
struct bnad {int dummy; } ;
struct bna_tcb {struct bnad* bnad; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bnad_tx_complete (struct bnad*,struct bna_tcb*) ; 

__attribute__((used)) static irqreturn_t
bnad_msix_tx(int irq, void *data)
{
	struct bna_tcb *tcb = (struct bna_tcb *)data;
	struct bnad *bnad = tcb->bnad;

	bnad_tx_complete(bnad, tcb);

	return IRQ_HANDLED;
}