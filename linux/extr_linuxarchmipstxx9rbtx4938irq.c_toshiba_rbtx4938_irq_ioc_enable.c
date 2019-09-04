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
struct irq_data {int irq; } ;

/* Variables and functions */
 int RBTX4938_IRQ_IOC ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  rbtx4938_imask_addr ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshiba_rbtx4938_irq_ioc_enable(struct irq_data *d)
{
	unsigned char v;

	v = readb(rbtx4938_imask_addr);
	v |= (1 << (d->irq - RBTX4938_IRQ_IOC));
	writeb(v, rbtx4938_imask_addr);
	mmiowb();
}