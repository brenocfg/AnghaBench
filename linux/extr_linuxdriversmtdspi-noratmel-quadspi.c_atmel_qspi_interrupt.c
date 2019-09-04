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
struct atmel_qspi {int pending; int /*<<< orphan*/  cmd_completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  QSPI_IMR ; 
 int /*<<< orphan*/  QSPI_SR ; 
 int QSPI_SR_CMD_COMPLETED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int qspi_readl (struct atmel_qspi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t atmel_qspi_interrupt(int irq, void *dev_id)
{
	struct atmel_qspi *aq = (struct atmel_qspi *)dev_id;
	u32 status, mask, pending;

	status = qspi_readl(aq, QSPI_SR);
	mask = qspi_readl(aq, QSPI_IMR);
	pending = status & mask;

	if (!pending)
		return IRQ_NONE;

	aq->pending |= pending;
	if ((aq->pending & QSPI_SR_CMD_COMPLETED) == QSPI_SR_CMD_COMPLETED)
		complete(&aq->cmd_completion);

	return IRQ_HANDLED;
}