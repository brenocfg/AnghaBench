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
struct gsc_irq {int irq; int /*<<< orphan*/  txn_data; int /*<<< orphan*/  txn_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_EIM_WIDTH ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  txn_alloc_addr (int) ; 
 int /*<<< orphan*/  txn_alloc_data (int) ; 
 int txn_alloc_irq (int /*<<< orphan*/ ) ; 

int gsc_alloc_irq(struct gsc_irq *i)
{
	int irq = txn_alloc_irq(GSC_EIM_WIDTH);
	if (irq < 0) {
		printk("cannot get irq\n");
		return irq;
	}

	i->txn_addr = txn_alloc_addr(irq);
	i->txn_data = txn_alloc_data(irq);
	i->irq = irq;

	return irq;
}