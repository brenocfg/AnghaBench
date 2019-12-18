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
struct b53_srab_priv {struct b53_srab_port_priv* port_intrs; } ;
struct b53_srab_port_priv {int irq_enabled; int /*<<< orphan*/  irq; } ;
struct b53_device {int /*<<< orphan*/  dev; struct b53_srab_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  b53_srab_port_isr ; 
 int /*<<< orphan*/  b53_srab_port_thread ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct b53_srab_port_priv*) ; 

__attribute__((used)) static int b53_srab_irq_enable(struct b53_device *dev, int port)
{
	struct b53_srab_priv *priv = dev->priv;
	struct b53_srab_port_priv *p = &priv->port_intrs[port];
	int ret = 0;

	/* Interrupt is optional and was not specified, do not make
	 * this fatal
	 */
	if (p->irq == -ENXIO)
		return ret;

	ret = request_threaded_irq(p->irq, b53_srab_port_isr,
				   b53_srab_port_thread, 0,
				   dev_name(dev->dev), p);
	if (!ret)
		p->irq_enabled = true;

	return ret;
}