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
struct hwbutton_interrupt {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handle_lo ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  eirq; int /*<<< orphan*/  (* handle_hi ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long* CIC_EXT_CFG_REG ; 
 scalar_t__ CIC_EXT_IS_ACTIVE_HI (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIC_EXT_SET_ACTIVE_HI (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIC_EXT_SET_ACTIVE_LO (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hwbutton_handler(int irq, void *data)
{
	struct hwbutton_interrupt *hirq = data;
	unsigned long cic_ext = *CIC_EXT_CFG_REG;

	if (CIC_EXT_IS_ACTIVE_HI(cic_ext, hirq->eirq)) {
		/* Interrupt: pin is now HI */
		CIC_EXT_SET_ACTIVE_LO(cic_ext, hirq->eirq);
		hirq->handle_hi(hirq->data);
	} else {
		/* Interrupt: pin is now LO */
		CIC_EXT_SET_ACTIVE_HI(cic_ext, hirq->eirq);
		hirq->handle_lo(hirq->data);
	}

	/*
	 * Invert the POLARITY of this level interrupt to ack the interrupt
	 * Thus next state change will invoke the opposite message
	 */
	*CIC_EXT_CFG_REG = cic_ext;

	return IRQ_HANDLED;
}