#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gfar_priv_grp {TYPE_1__* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ievent; } ;

/* Variables and functions */
 int IEVENT_ERR_MASK ; 
 int IEVENT_RX_MASK ; 
 int IEVENT_TX_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gfar_error (int,void*) ; 
 int gfar_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_receive (int,void*) ; 
 int /*<<< orphan*/  gfar_transmit (int,void*) ; 

__attribute__((used)) static irqreturn_t gfar_interrupt(int irq, void *grp_id)
{
	struct gfar_priv_grp *gfargrp = grp_id;

	/* Save ievent for future reference */
	u32 events = gfar_read(&gfargrp->regs->ievent);

	/* Check for reception */
	if (events & IEVENT_RX_MASK)
		gfar_receive(irq, grp_id);

	/* Check for transmit completion */
	if (events & IEVENT_TX_MASK)
		gfar_transmit(irq, grp_id);

	/* Check for errors */
	if (events & IEVENT_ERR_MASK)
		gfar_error(irq, grp_id);

	return IRQ_HANDLED;
}