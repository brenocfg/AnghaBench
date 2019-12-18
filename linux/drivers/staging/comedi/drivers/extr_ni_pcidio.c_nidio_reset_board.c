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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ MASTER_DMA_AND_INTERRUPT_CONTROL ; 
 scalar_t__ PORT_IO (int /*<<< orphan*/ ) ; 
 scalar_t__ PORT_PIN_DIRECTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ PORT_PIN_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nidio_reset_board(struct comedi_device *dev)
{
	writel(0, dev->mmio + PORT_IO(0));
	writel(0, dev->mmio + PORT_PIN_DIRECTIONS(0));
	writel(0, dev->mmio + PORT_PIN_MASK(0));

	/* disable interrupts on board */
	writeb(0, dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);
}