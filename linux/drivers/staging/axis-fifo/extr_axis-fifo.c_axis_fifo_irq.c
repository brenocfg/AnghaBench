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
struct axis_fifo {scalar_t__ base_addr; int /*<<< orphan*/  dt_device; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ XLLF_IER_OFFSET ; 
 unsigned int XLLF_INT_ALL_MASK ; 
 unsigned int XLLF_INT_RC_MASK ; 
 unsigned int XLLF_INT_RFPE_MASK ; 
 unsigned int XLLF_INT_RFPF_MASK ; 
 unsigned int XLLF_INT_RPORE_MASK ; 
 unsigned int XLLF_INT_RPUE_MASK ; 
 unsigned int XLLF_INT_RPURE_MASK ; 
 unsigned int XLLF_INT_RRC_MASK ; 
 unsigned int XLLF_INT_TC_MASK ; 
 unsigned int XLLF_INT_TFPE_MASK ; 
 unsigned int XLLF_INT_TFPF_MASK ; 
 unsigned int XLLF_INT_TPOE_MASK ; 
 unsigned int XLLF_INT_TRC_MASK ; 
 unsigned int XLLF_INT_TSE_MASK ; 
 scalar_t__ XLLF_ISR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t axis_fifo_irq(int irq, void *dw)
{
	struct axis_fifo *fifo = (struct axis_fifo *)dw;
	unsigned int pending_interrupts;

	do {
		pending_interrupts = ioread32(fifo->base_addr +
					      XLLF_IER_OFFSET) &
					      ioread32(fifo->base_addr
					      + XLLF_ISR_OFFSET);
		if (pending_interrupts & XLLF_INT_RC_MASK) {
			/* packet received */

			/* wake the reader process if it is waiting */
			wake_up(&fifo->read_queue);

			/* clear interrupt */
			iowrite32(XLLF_INT_RC_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TC_MASK) {
			/* packet sent */

			/* wake the writer process if it is waiting */
			wake_up(&fifo->write_queue);

			iowrite32(XLLF_INT_TC_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TFPF_MASK) {
			/* transmit fifo programmable full */

			iowrite32(XLLF_INT_TFPF_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TFPE_MASK) {
			/* transmit fifo programmable empty */

			iowrite32(XLLF_INT_TFPE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RFPF_MASK) {
			/* receive fifo programmable full */

			iowrite32(XLLF_INT_RFPF_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RFPE_MASK) {
			/* receive fifo programmable empty */

			iowrite32(XLLF_INT_RFPE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TRC_MASK) {
			/* transmit reset complete interrupt */

			iowrite32(XLLF_INT_TRC_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RRC_MASK) {
			/* receive reset complete interrupt */

			iowrite32(XLLF_INT_RRC_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RPURE_MASK) {
			/* receive fifo under-read error interrupt */
			dev_err(fifo->dt_device,
				"receive under-read interrupt\n");

			iowrite32(XLLF_INT_RPURE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RPORE_MASK) {
			/* receive over-read error interrupt */
			dev_err(fifo->dt_device,
				"receive over-read interrupt\n");

			iowrite32(XLLF_INT_RPORE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_RPUE_MASK) {
			/* receive underrun error interrupt */
			dev_err(fifo->dt_device,
				"receive underrun error interrupt\n");

			iowrite32(XLLF_INT_RPUE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TPOE_MASK) {
			/* transmit overrun error interrupt */
			dev_err(fifo->dt_device,
				"transmit overrun error interrupt\n");

			iowrite32(XLLF_INT_TPOE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts & XLLF_INT_TSE_MASK) {
			/* transmit length mismatch error interrupt */
			dev_err(fifo->dt_device,
				"transmit length mismatch error interrupt\n");

			iowrite32(XLLF_INT_TSE_MASK & XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		} else if (pending_interrupts) {
			/* unknown interrupt type */
			dev_err(fifo->dt_device,
				"unknown interrupt(s) 0x%x\n",
				pending_interrupts);

			iowrite32(XLLF_INT_ALL_MASK,
				  fifo->base_addr + XLLF_ISR_OFFSET);
		}
	} while (pending_interrupts);

	return IRQ_HANDLED;
}