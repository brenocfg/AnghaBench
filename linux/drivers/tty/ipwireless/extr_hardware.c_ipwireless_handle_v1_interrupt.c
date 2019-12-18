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
struct ipw_hardware {int tx_ready; int /*<<< orphan*/  tasklet; scalar_t__ base_port; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_ready; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IOIR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned short IR_RXINTR ; 
 unsigned short IR_TXINTR ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ipwireless_handle_v1_interrupt(int irq,
						  struct ipw_hardware *hw)
{
	unsigned short irqn;

	irqn = inw(hw->base_port + IOIR);

	/* Check if card is present */
	if (irqn == 0xFFFF)
		return IRQ_NONE;
	else if (irqn != 0) {
		unsigned short ack = 0;
		unsigned long flags;

		/* Transmit complete. */
		if (irqn & IR_TXINTR) {
			ack |= IR_TXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->tx_ready = 1;
			spin_unlock_irqrestore(&hw->lock, flags);
		}
		/* Received data */
		if (irqn & IR_RXINTR) {
			ack |= IR_RXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->rx_ready++;
			spin_unlock_irqrestore(&hw->lock, flags);
		}
		if (ack != 0) {
			outw(ack, hw->base_port + IOIR);
			tasklet_schedule(&hw->tasklet);
		}
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}