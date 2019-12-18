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
struct pic32_spi {scalar_t__ rx_end; scalar_t__ rx; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  fault_irq; int /*<<< orphan*/  (* rx_fifo ) (struct pic32_spi*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pic32_spi*) ; 

__attribute__((used)) static irqreturn_t pic32_spi_rx_irq(int irq, void *dev_id)
{
	struct pic32_spi *pic32s = dev_id;

	pic32s->rx_fifo(pic32s);

	/* rx complete ? */
	if (pic32s->rx_end == pic32s->rx) {
		/* disable all interrupts */
		disable_irq_nosync(pic32s->fault_irq);
		disable_irq_nosync(pic32s->rx_irq);

		/* complete current xfer */
		complete(&pic32s->xfer_done);
	}

	return IRQ_HANDLED;
}