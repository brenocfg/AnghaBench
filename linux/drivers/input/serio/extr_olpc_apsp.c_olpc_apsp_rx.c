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
struct serio {int dummy; } ;
struct olpc_apsp {int /*<<< orphan*/  dev; scalar_t__ base; struct serio* padio; struct serio* kbio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ COMMAND_RETURN_STATUS ; 
 unsigned int DATA_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ KEYBOARD_PORT ; 
 scalar_t__ PJ_RST_INTERRUPT ; 
 unsigned int PORT_MASK ; 
 scalar_t__ PORT_SHIFT ; 
 scalar_t__ SECURE_PROCESSOR_COMMAND ; 
 unsigned int SP_COMMAND_COMPLETE_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t olpc_apsp_rx(int irq, void *dev_id)
{
	struct olpc_apsp *priv = dev_id;
	unsigned int w, tmp;
	struct serio *serio;

	/*
	 * Write 1 to PJ_RST_INTERRUPT to acknowledge and clear the interrupt
	 * Write 0xff00 to SECURE_PROCESSOR_COMMAND.
	 */
	tmp = readl(priv->base + PJ_RST_INTERRUPT);
	if (!(tmp & SP_COMMAND_COMPLETE_RESET)) {
		dev_warn(priv->dev, "spurious interrupt?\n");
		return IRQ_NONE;
	}

	w = readl(priv->base + COMMAND_RETURN_STATUS);
	dev_dbg(priv->dev, "olpc_apsp_rx %x\n", w);

	if (w >> PORT_SHIFT == KEYBOARD_PORT)
		serio = priv->kbio;
	else
		serio = priv->padio;

	serio_interrupt(serio, w & DATA_MASK, 0);

	/* Ack and clear interrupt */
	writel(tmp | SP_COMMAND_COMPLETE_RESET, priv->base + PJ_RST_INTERRUPT);
	writel(PORT_MASK, priv->base + SECURE_PROCESSOR_COMMAND);

	pm_wakeup_event(priv->dev, 1000);
	return IRQ_HANDLED;
}