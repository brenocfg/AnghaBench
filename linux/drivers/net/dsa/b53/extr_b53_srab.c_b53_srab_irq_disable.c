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
struct b53_device {struct b53_srab_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct b53_srab_port_priv*) ; 

__attribute__((used)) static void b53_srab_irq_disable(struct b53_device *dev, int port)
{
	struct b53_srab_priv *priv = dev->priv;
	struct b53_srab_port_priv *p = &priv->port_intrs[port];

	if (p->irq_enabled) {
		free_irq(p->irq, p);
		p->irq_enabled = false;
	}
}