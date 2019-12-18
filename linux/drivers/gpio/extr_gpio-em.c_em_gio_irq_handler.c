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
struct em_gio_priv {int /*<<< orphan*/  irq_domain; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  GIO_IIR ; 
 int /*<<< orphan*/  GIO_MST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long em_gio_read (struct em_gio_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_gio_write (struct em_gio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t em_gio_irq_handler(int irq, void *dev_id)
{
	struct em_gio_priv *p = dev_id;
	unsigned long pending;
	unsigned int offset, irqs_handled = 0;

	while ((pending = em_gio_read(p, GIO_MST))) {
		offset = __ffs(pending);
		em_gio_write(p, GIO_IIR, BIT(offset));
		generic_handle_irq(irq_find_mapping(p->irq_domain, offset));
		irqs_handled++;
	}

	return irqs_handled ? IRQ_HANDLED : IRQ_NONE;
}