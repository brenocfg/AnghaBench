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
struct pdc_intc_priv {int /*<<< orphan*/  lock; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int PDC_SYS_WAKE_BASE ; 
 unsigned int PDC_SYS_WAKE_INT_CHANGE ; 
 unsigned int PDC_SYS_WAKE_INT_DOWN ; 
 unsigned int PDC_SYS_WAKE_INT_HIGH ; 
 unsigned int PDC_SYS_WAKE_INT_LOW ; 
 unsigned int PDC_SYS_WAKE_INT_MODE ; 
 unsigned int PDC_SYS_WAKE_INT_MODE_SHIFT ; 
 unsigned int PDC_SYS_WAKE_INT_UP ; 
 unsigned int PDC_SYS_WAKE_STRIDE ; 
 unsigned int hwirq_to_syswake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_setup_alt_chip (struct irq_data*,unsigned int) ; 
 struct pdc_intc_priv* irqd_to_priv (struct irq_data*) ; 
 unsigned int pdc_read (struct pdc_intc_priv*,unsigned int) ; 
 int /*<<< orphan*/  pdc_write (struct pdc_intc_priv*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int syswake_irq_set_type(struct irq_data *data, unsigned int flow_type)
{
	struct pdc_intc_priv *priv = irqd_to_priv(data);
	unsigned int syswake = hwirq_to_syswake(data->hwirq);
	unsigned int irq_mode;
	unsigned int soc_sys_wake_regoff, soc_sys_wake;

	/* translate to syswake IRQ mode */
	switch (flow_type) {
	case IRQ_TYPE_EDGE_BOTH:
		irq_mode = PDC_SYS_WAKE_INT_CHANGE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		irq_mode = PDC_SYS_WAKE_INT_UP;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irq_mode = PDC_SYS_WAKE_INT_DOWN;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irq_mode = PDC_SYS_WAKE_INT_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irq_mode = PDC_SYS_WAKE_INT_LOW;
		break;
	default:
		return -EINVAL;
	}

	raw_spin_lock(&priv->lock);

	/* set the IRQ mode */
	soc_sys_wake_regoff = PDC_SYS_WAKE_BASE + syswake*PDC_SYS_WAKE_STRIDE;
	soc_sys_wake = pdc_read(priv, soc_sys_wake_regoff);
	soc_sys_wake &= ~PDC_SYS_WAKE_INT_MODE;
	soc_sys_wake |= irq_mode << PDC_SYS_WAKE_INT_MODE_SHIFT;
	pdc_write(priv, soc_sys_wake_regoff, soc_sys_wake);

	/* and update the handler */
	irq_setup_alt_chip(data, flow_type);

	raw_spin_unlock(&priv->lock);

	return 0;
}