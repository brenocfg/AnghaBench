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
struct b53_srab_priv {scalar_t__ regs; } ;
struct b53_srab_port_priv {int /*<<< orphan*/  num; struct b53_device* dev; } ;
struct b53_device {struct b53_srab_priv* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ B53_SRAB_INTR ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t b53_srab_port_isr(int irq, void *dev_id)
{
	struct b53_srab_port_priv *port = dev_id;
	struct b53_device *dev = port->dev;
	struct b53_srab_priv *priv = dev->priv;

	/* Acknowledge the interrupt */
	writel(BIT(port->num), priv->regs + B53_SRAB_INTR);

	return IRQ_WAKE_THREAD;
}