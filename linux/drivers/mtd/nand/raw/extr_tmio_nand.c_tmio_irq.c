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
struct tmio_nand {int /*<<< orphan*/  comp; scalar_t__ fcr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ FCR_IMR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tmio_irq(int irq, void *__tmio)
{
	struct tmio_nand *tmio = __tmio;

	/* disable RDYREQ interrupt */
	tmio_iowrite8(0x00, tmio->fcr + FCR_IMR);
	complete(&tmio->comp);

	return IRQ_HANDLED;
}